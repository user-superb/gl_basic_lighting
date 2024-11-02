#include "camera.hpp"

#include <iostream>

Camera::Camera(unsigned int widthIn, unsigned int heightIn, glm::vec3 positionIn):
width(widthIn),
height(heightIn),
position(positionIn)
{}

void Camera::update(Shader shaderIn, const char* uniformName) 
{
    glUseProgram(shaderIn.ID);

    /* Posición y Orientación */
    glm::mat4 view = glm::lookAt(position, position + orientation, up);
    
    /* Perspectiva */
    glm::mat4 proj = glm::perspective(glm::radians(fov), (float)width / height, nearPlane, farPlane);

    /* Asignar valores */
    glUniformMatrix4fv(glGetUniformLocation(shaderIn.ID, uniformName), 1, GL_FALSE, glm::value_ptr(proj * view));
}

glm::mat4 Camera::getView() {
	return glm::lookAt(position, position + orientation, up);
}

void Camera::input(GLFWwindow *windowIn) 
{
    /******************/
    /* Desplazamiento */
    /******************/

    /* 
        Desplazamiento sobre el plano XY
        W, A, S, D
    */
    if (glfwGetKey(windowIn, GLFW_KEY_W) == GLFW_PRESS) 
    {
        position += speed * orientation;
    }
    if (glfwGetKey(windowIn, GLFW_KEY_S) == GLFW_PRESS) 
    {
        position += speed * -orientation;
    }
    if (glfwGetKey(windowIn, GLFW_KEY_A) == GLFW_PRESS) 
    {
        position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(windowIn, GLFW_KEY_D) == GLFW_PRESS) 
    {
        position += speed * glm::normalize(glm::cross(orientation, up));
    }

    /* 
        SUBIR   , BAJAR
        ESPACIO , CTRL_IZQUIERDO
    */
    if (glfwGetKey(windowIn, GLFW_KEY_SPACE) == GLFW_PRESS) 
    {
        position += speed * up;
    }
    if (glfwGetKey(windowIn, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) 
    {
        position += speed * -up;
    }

    /*
        INCREMENTAR VELOCIDAD
        SHIFT
    */
    if (glfwGetKey(windowIn, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
    {
        speed = 0.4f;
    } 
    else if (glfwGetKey(windowIn, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.1f;
    }

    /************/
    /* Rotación */
    /************/
    static bool firstClick = true;
    if (glfwGetMouseButton(windowIn, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
    {
        /* Desactiva el cursor */
        glfwSetInputMode(windowIn, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        /* Coordenadas del mouse */
        double  mouseX,
                mouseY;
        glfwGetCursorPos(windowIn, &mouseX, &mouseY);

        static float lastX = mouseX;
        static float lastY = mouseY;

        /* Previene que la vista salte hacia un punto al clickear en la ventana */
        if (firstClick)
		{
			lastX = mouseX;
            lastY = mouseY;
			firstClick = false;
		}

        float xOffset = (mouseX - lastX) * sensitivity;
        float yOffset = (lastY - mouseY) * sensitivity; 
        lastX = mouseX;
        lastY = mouseY;

        yaw   += xOffset; // Rotación sobre el eje Y
        pitch += yOffset; // Rotación sobre el eje X

        /* 
            Establece un limite de la camara para que la rotación sobre el eje X no supere °90 o quede por debajo de °-90 
        */
        if(pitch > 89.0f)
            pitch =  89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        /* Math stuff */
        glm::vec3 direction ( // Nueva dirección                // Components
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),  // X
            sin(glm::radians(pitch)),                           // Y
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))   // Z
        );
        /* Sets the new direction */
        orientation = glm::normalize(direction);
    } 
    else if (glfwGetMouseButton(windowIn, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        /* Restaura el cursor */
        glfwSetInputMode(windowIn, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

