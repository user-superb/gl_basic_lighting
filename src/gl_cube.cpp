#include "gl_cube.hpp"

#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

Cube::Cube(Shader shaderProgram):
_shaderProgram(shaderProgram)
{
    /*
        Nota: Se deben crear las variables como estaticas ya que al finalizar
        la memoria es liberada.
    */
    static VAO VAO0 = VAO();
    VAO0.bind();

    static VBO VBO0 = VBO(vertices, sizeof(vertices));
    VBO0.bind();

    VAO0.linkAttributes(VBO0, 0, 3, GL_FLOAT, sizeof(GLfloat) * 6, (void*)0);
    VAO0.linkAttributes(VBO0, 1, 3, GL_FLOAT, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));

    VAO0.unbind();
    VBO0.unbind();

    /* Asignar direcciones */
    _VAO = &VAO0;
    _VBO = &VBO0;
}

void Cube::draw() 
{
    /* Enlazar VertexArrayBuffer */
    _VAO->bind();

    /* Enlazar shader */
    _shaderProgram.use();

    // Buscar la localización de la variable 'model'
    GLuint modelLocation = glGetUniformLocation(_shaderProgram.ID, "model");
    // Asignar valor
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_matrix));

    // Dibujar
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::resetPosition()
{
    /*
        Nota: _matrix = glm::mat4(1.0f); reinicia todos los valores
        incluida la rotación.
    */

    _matrix[3][0] = 0.0f;
    _matrix[3][1] = 0.0f;
    _matrix[3][2] = 0.0f;

    pos = glm::vec3(0.0f);
}

void Cube::setPosition(glm::vec3 position) 
{
    // Reiniciar posición
    Cube::resetPosition();

    // Trasladar desde 0.0
    Cube::translate(position);
}

void Cube::translate(glm::vec3 position)
{
    pos = position;
    _matrix = glm::translate(_matrix, position);
}

void Cube::rotate(float angle, glm::vec3 axis) 
{
    _matrix = glm::rotate(_matrix, angle, axis);
}