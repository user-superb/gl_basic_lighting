#ifndef GL_CUBE
#define GL_CUBE

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

class Cube {
private:
    /*
            Tambien se podria interpretar como 'modelo' al 'mundo' (model to world),
        despues la camara se encarga de convertir del 'mundo' a 'vista' (world to view)
        y de 'vista' a 'proyección' (view to projection).
    */
    glm::mat4 _matrix       = glm::mat4(1.0f);

    Shader _shaderProgram;

    VAO *_VAO = nullptr;
    VBO *_VBO = nullptr;
public:
    glm::vec3 objectColor = glm::vec3(1.0f);
    glm::vec3 pos = glm::vec3(0.0f);

    // Constructor
    Cube(Shader shaderProgram);

    /*
        Reinicia la posición al punto de origen.
    */
    void resetPosition();
    
    /*
        La función posiciona el cubo en las coordenadas especificadas.
    */
    void setPosition(glm::vec3 position);
    
    /*
        La función traslada el cubo con respecto a la posición actual.
    */
    void translate(glm::vec3 position);
    
    /*
        La función espera recibir el angulo en radianes y
    un vector unitario que especifique el angulo a rotar.
        Ejemplo: <1.0f, 0.0f, 0.0f>, donde girara sobre el eje X.
    */
    void rotate(float angle, glm::vec3 axis);

    void draw();
};

#endif