#include <fstream>
#include <sstream>

#include "shader.hpp"

#include <iostream>

// Shader::Constructor()
// ---------------------
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Notas:
    //      Falta comprobar errores al leer, compilar y enlazar.

    /*1. Lectura de Archivos */
    std::ifstream   vertexSourceFile,
                    fragmentSourceFile;
    std::string     vertexCode,
                    fragmentCode;
    std::stringstream   vertexStream,
                        fragmentStream;

    /* Me aseguro que los objetos puedan tirar 'Excepciones'*/
    vertexSourceFile.exceptions     (std::ifstream::failbit | std::ifstream::badbit);
    fragmentSourceFile.exceptions   (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        /* Apertura de archivos */
        vertexSourceFile.open(vertexPath);
        fragmentSourceFile.open(fragmentPath);
        /* Transfiere el contenido del buffer de los archivos en 'stream' */
        vertexStream    << vertexSourceFile.rdbuf();
        fragmentStream  << fragmentSourceFile.rdbuf();
        /* Cierre de los archivos*/
        vertexSourceFile.close();
        fragmentSourceFile.close();
        /* Conversión de 'stream' a 'string'*/
        vertexCode      = vertexStream.str(),
        fragmentCode    = fragmentStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderCode    = vertexCode.c_str();
    const char* fragmentShaderCode  = fragmentCode.c_str();
    
    /*2. Compilación de Shaders */
    int success = 0;
    char infoLog[512];

    GLuint  vertexShader    = glCreateShader(GL_VERTEX_SHADER),
            fragmentShader  = glCreateShader(GL_FRAGMENT_SHADER);

    /* Vertex Shader */
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    /* Error handling */
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "(file: " << vertexPath << ")" << std::endl << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* Fragment Shader */
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    /* Error handling */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "(file: " << fragmentPath << ")" << std::endl << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* Shader Program */
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    /* Error handling */
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_ERROR\n" << infoLog << std::endl;
    }

    /*3. Limpieza */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Shader::use()
// -------------
void Shader::use() 
{
    glUseProgram(ID);
}

// Shader::setTYPE()
// ----------------
void Shader::setBool(const std::string &name, bool value) const
{
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniform1ui(uniformLocation, value);
}
void Shader::setInt(const std::string &name, int value) const
{
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniform1i(uniformLocation, value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniform1f(uniformLocation, value);
}
void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}
