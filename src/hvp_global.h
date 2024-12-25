#ifndef HVP_GLOBAL_H
#define HVP_GLOBAL_H

#include <GLFW/glfw3.h>

// Main and only window to be displayed
GLFWwindow* HVPG_window;

#define HVP_TARGET_FPS 24
#define HVP_FRAME_DURATION (1.0 / HVP_TARGET_FPS)

int HVPG_renderer_width, HVPG_renderer_height;
int HVPG_window_width, HVPG_window_height;



#endif // !HVP_GLOBAL_H
