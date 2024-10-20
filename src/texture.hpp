#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Texture {
public:
    GLuint ID   = -1;
    GLenum type = 0;

    Texture(const char* imagePath, GLenum format, GLenum textureType, GLenum slot);

    void bind();
    void unbind();
};

#endif

