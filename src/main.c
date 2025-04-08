#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/console_logger.h"
#include "utils/file_system.h"

#include "hvp_global.h"


void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void _window_size_callback(GLFWwindow* window, int width, int height) {
    HVPG_window_width = width;
    HVPG_window_height = height;
}


int main() {
    FS_working_directory_set_path("resources");

    if (!glfwInit()) {
        console_print(C_ERROR, "failed initializing GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    HVPG_window = glfwCreateWindow(800, 600, "MoonStation", NULL, NULL);
    if (!HVPG_window) {
        console_print(C_ERROR, "failed initializing the GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(HVPG_window);

    glfwSwapInterval(1);

    glfwGetWindowSize(HVPG_window, &HVPG_window_width, &HVPG_window_height);
    glfwSetWindowSizeCallback(HVPG_window, _window_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        console_print(C_ERROR, "failed initializing glad");
        return -1;
    }

    HVPG_framebuffer = HVP_framebuffer_init(320, 240, "shaders/fragment_screen.frag");

    HVP_Framebuffer* crt_FB = HVP_framebuffer_init(640, 480, "shaders/crt_screen.frag");
    HVP_shader_set_vector2_f(HVP_framebuffer_get_shader(crt_FB), "screen_resolution", 320, 240);

    double last_update_time = 0;
    double last_frame_time = 0;

    while (!glfwWindowShouldClose(HVPG_window)) {
        double current_time = glfwGetTime();
        double dt = current_time - last_update_time;

        glfwPollEvents();


        if ((current_time - last_frame_time) >= HVP_FRAME_DURATION) {
            HVP_framebuffer_begin_frame(HVPG_framebuffer);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            HVP_framebuffer_end_frame(HVPG_framebuffer, true);

            glfwSwapBuffers(HVPG_window);

            last_frame_time = current_time;
        }
        last_update_time = current_time;
    }

    HVP_framebuffer_destroy(HVPG_framebuffer);
    glfwDestroyWindow(HVPG_window);

    glfwTerminate();
    return 0;
}

