#include "VBO.hpp"

/* Constructor */
VBO::VBO(GLfloat* vertices, GLsizeiptr size) 
{
    /* Generar buffer */
    glGenBuffers(1, &(VBO::ID));
    /* Enlazar buffer */
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    /* Almacenar datos del buffer */
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() 
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}