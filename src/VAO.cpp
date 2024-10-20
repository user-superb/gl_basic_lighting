#include "VAO.hpp"

/* Constructor */
VAO::VAO() 
{
    /* Generar VAO */
    glGenVertexArrays(1, &(VAO::ID));
}

void VAO::linkAttributes(VBO &VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* pointer) 
{
    VBO.bind();

    /* Asignar atributos */
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, pointer);
    /* Habilitar atributos para la posición 'layout' */
    glEnableVertexAttribArray(layout);

    VBO.unbind();
}

void VAO::bind() 
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}