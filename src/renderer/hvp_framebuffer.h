#ifndef HVP_FRAMEBUFFER_H
#define HVP_FRAMEBUFFER_H

#include <glad/glad.h>

#include "hvp_shader.h"

// Framebuffer Object struct
typedef struct {
	GLuint ID;

	int r_width;
	int r_height;
	int r_color_depth;

	GLuint FBO;
	GLuint FBO_TEX;
	GLuint RBO;

	GLuint SQ_VAO, SQ_VBO;
	HVP_Shader* FBO_SHADER;

} HVP_Framebuffer;

HVP_Framebuffer* HVP_framebuffer_init(int width, int heigth, const char* fragment_path);
void HVP_framebuffer_destroy(HVP_Framebuffer* framebuffer_id);

void HVP_framebuffer_begin_frame(HVP_Framebuffer* framebuffer_id);
void HVP_framebuffer_end_frame(HVP_Framebuffer* framebuffer_id, bool apply_letterbox);

HVP_Shader* HVP_framebuffer_get_shader(HVP_Framebuffer* framebuffer_id);

void HVPM_framebuffer_init_screen_quad(HVP_Framebuffer* framebuffer_id);

#endif // !HVP_FRAMEBUFFER_H
