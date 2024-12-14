#include "hvp_rendering_chip.h"

#include <stdlib.h>

#include "utils/console_logger.h"


// Initializes GLFW and the OpenGL context using glad, creating a <GLFW window>
void HVPGPU_OGL_init(int m_window_width, int m_window_height) {
    if (!glfwInit()) {
        console_print(C_ERROR, "Failed initializing GLFW");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    HVPG_window = glfwCreateWindow(m_window_width, m_window_height, "MoonStation", NULL, NULL);
    if (!HVPG_window) {
        console_print(C_ERROR, "Failed initializing the GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(HVPG_window);

    //glfwSetKeyCallback(ms_window, _key_callback);
    //glfwGetWindowSize(ms_window, &window_width, &window_height);
    //glfwSetWindowSizeCallback(ms_window, _window_size_callback);
    //glfwSetFramebufferSizeCallback(ms_window, _framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        console_print(C_ERROR, "Failed initializing Glad");
        exit(EXIT_FAILURE);
    }

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}
