#ifndef VBO_HPP
#define VBO_HPP

#include "glad/glad.h"

/* Vertex Buffer Object */
class VBO {
public:
    GLuint ID = 0;

    VBO(GLfloat *vertices, GLsizeiptr size);

    void bind();
    void unbind();
};

#endif