#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "hvp_global.h"

extern GLFWwindow* HVPG_window;

// Initializes GLFW and the OpenGL context using glad, creating a <GLFW window>
void HVPGPU_OGL_init(int m_window_width, int m_window_height);

