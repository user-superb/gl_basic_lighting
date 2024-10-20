#ifndef EBO_HPP
#define EBO_HPP

#include "glad/glad.h"

/* Element Buffer Object */
class EBO {
public:
    GLuint ID = 0;

    EBO(GLuint* indices, GLsizeiptr size);

    void bind();
    void unbind();
};

#endif