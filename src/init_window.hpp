#ifndef INIT_WINDOW_HPP
#define INIT_WINDOW_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow* initWindow(const char* title, int SCR_WIDTH, int SRC_HEIGHT); 

#endif