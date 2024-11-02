#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

class Camera {
public:
    glm::vec3       position    = glm::vec3(0.0f, 0.0f, 3.0f),
                    orientation = glm::vec3(0.0f, 0.0f, -1.0f),
                    up          = glm::vec3(0.0f, 1.0f, 0.0f);
    unsigned int    width       = 0,
                    height      = 0;

    float           speed = 0.1f,       // Movement
                    sensitivity = 0.1f; // Rotation

    float           fov         = 45.0f,
                    nearPlane   = 0.01f,
                    farPlane    = 100.0f;

    /* Math */
    float           yaw     = -90.0f,
                    pitch   = 0;

    Camera(unsigned int widthIn, unsigned int heightIn, glm::vec3 positionIn);

    /* Updates the camera's view and fov, and send it to the ShaderProgram */
    void update(Shader shaderIn, const char* uniformName);
    /* Checks input and update de camera position and orientation vector */
    void input(GLFWwindow *windowIn);

    glm::mat4 getView();
};

#endif
