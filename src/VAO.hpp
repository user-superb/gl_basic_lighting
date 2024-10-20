#ifndef VAO_HPP
#define VAO_HPP

#include "glad/glad.h"

#include "VBO.hpp"

/* Vertex Array Object */
class VAO {
public:
    GLuint ID = 0;

    VAO();

    void linkAttributes(VBO &VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* pointer);    

    void bind();
    void unbind();
};

#endif