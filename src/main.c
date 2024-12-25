#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/console_logger.h"
#include "hvp_global.h"


int main() {
    console_print(C_INFO, "Lol");
    console_print(C_WARNING, "Lol");
    console_print(C_ERROR, "Lol");

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

    //glfwSetKeyCallback(ms_window, _key_callback);
    //glfwGetWindowSize(ms_window, &window_width, &window_height);
    //glfwSetWindowSizeCallback(ms_window, _window_size_callback);
    //glfwSetFramebufferSizeCallback(ms_window, _framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        console_print(C_ERROR, "failed initializing glad");
        return -1;
    }

    while (!glfwWindowShouldClose(HVPG_window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(HVPG_window);
        glfwPollEvents();
    }


    glfwDestroyWindow(HVPG_window);

    glfwTerminate();
    return 0;
}

