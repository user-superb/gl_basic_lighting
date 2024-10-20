#include "init_window.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

GLFWwindow* initWindow(const char* WINDOW_TITLE, int SCR_WIDTH, int SRC_HEIGHT) 
{
    GLFWwindow *window;

    // glfw: Inicializar
    // ----------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // glfw: Crear ventana
    // ------------------
    window = glfwCreateWindow(SCR_WIDTH, SRC_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        std::cout << "ERROR::GLFW::WINDOW::COULDNT_CREATE_THE_WINDOW\n" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glfw: Cargar funciones de opengl
    // ---------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("ERROR::GLAD::COULDNT_INIT_GLAD\n");
		return nullptr;
	}

    return window;
}