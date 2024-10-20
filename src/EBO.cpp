#include "EBO.hpp"

/* Constructor */
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
    /* Generar buffer */
    glGenBuffers(1, &(EBO::ID));
    /* Enlazar buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    /* Almacenar datos del buffer*/
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}