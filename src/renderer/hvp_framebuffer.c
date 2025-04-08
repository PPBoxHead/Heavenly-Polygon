#include "hvp_framebuffer.h"

#include "../hvp_global.h"

#include "../utils/console_logger.h"
#include "../utils/file_system.h"


HVP_Framebuffer* HVP_framebuffer_init(int render_width, int render_height, const char* fragment_path) {
    HVP_Framebuffer* framebuffer = (HVP_Framebuffer*)malloc(sizeof(HVP_Framebuffer));
    if (framebuffer) {
        framebuffer->r_width = render_width;
        framebuffer->r_height = render_height;

        HVPM_framebuffer_init_screen_quad(framebuffer);

        const char* vertex_buffer = FS_file_get_buffer("shaders/screen.vert");
        const char* fragment_buffer = FS_file_get_buffer(fragment_path);

        framebuffer->FBO_SHADER = HVP_shader_init();
        HVP_shader_compile(framebuffer->FBO_SHADER, vertex_buffer, fragment_buffer);

        HVP_shader_use(framebuffer->FBO_SHADER);
        HVP_shader_set_int(framebuffer->FBO_SHADER, "screenTexture", 0);

        glGenFramebuffers(1, &framebuffer->ID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->ID);

        glGenTextures(1, &framebuffer->FBO_TEX);
        glBindTexture(GL_TEXTURE_2D, framebuffer->FBO_TEX);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, framebuffer->r_width, framebuffer->r_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->FBO_TEX, 0);

        glGenRenderbuffers(1, &framebuffer->RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer->r_width, framebuffer->r_height); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer->RBO); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            console_print(C_ERROR, "Framebuffer is not complete!");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    return framebuffer;
}
// Add definition
void HVP_framebuffer_destroy(HVP_Framebuffer* framebuffer_id) {
    glDeleteVertexArrays(1, &framebuffer_id->SQ_VAO);
    glDeleteBuffers(1, &framebuffer_id->SQ_VBO);
    glDeleteRenderbuffers(1, &framebuffer_id->RBO);
    glDeleteFramebuffers(1, &framebuffer_id->ID);

    HVP_shader_destroy(framebuffer_id->FBO_SHADER);

    free(framebuffer_id);
}

// Add definiton
void HVP_framebuffer_begin_frame(HVP_Framebuffer* framebuffer_id) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id->ID);
    glViewport(0, 0, framebuffer_id->r_width, framebuffer_id->r_height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
// Add definition
void HVP_framebuffer_end_frame(HVP_Framebuffer* framebuffer_id, bool apply_letterbox) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

    if (apply_letterbox) {
        // Window Aspect Ratio
        float w_aspect = (float)HVPG_window_width / (float)HVPG_window_height;
        // Render Aspect Ratio
        float r_aspect = (float)framebuffer_id->r_width / (float)framebuffer_id->r_height;

        int viewport_x = 0, viewport_y = 0;
        int viewport_width = HVPG_window_width, viewport_height = HVPG_window_height;

        if (w_aspect > r_aspect) {
            viewport_height = HVPG_window_height;
            viewport_width = (int)(r_aspect * viewport_height);
            viewport_x = (HVPG_window_width - viewport_width) / 2;
        }
        else {
            viewport_width = HVPG_window_width;
            viewport_height = (int)(viewport_width / r_aspect);
            viewport_y = (HVPG_window_height - viewport_height) / 2;
        }

        glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    HVP_shader_use(framebuffer_id->FBO_SHADER);
    glBindVertexArray(framebuffer_id->SQ_VAO);
    glBindTexture(GL_TEXTURE_2D, framebuffer_id->FBO_TEX);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

HVP_Shader* HVP_framebuffer_get_shader(HVP_Framebuffer* framebuffer_id) {
    return framebuffer_id->FBO_SHADER;
}

void HVPM_framebuffer_init_screen_quad(HVP_Framebuffer* framebuffer_id) {
    float _vertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &framebuffer_id->SQ_VAO);
    glGenBuffers(1, &framebuffer_id->SQ_VBO);
    glBindVertexArray(framebuffer_id->SQ_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, framebuffer_id->SQ_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), &_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
