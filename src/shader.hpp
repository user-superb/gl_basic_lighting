#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader 
{
public:
    unsigned int ID = -1;
    // Constructor
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use shader
    void use();

    // Uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif
