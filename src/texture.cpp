#include "texture.hpp"

#include "stb/stb_image.h"
#include <iostream>

Texture::Texture(const char* imagePath, GLenum format, GLenum textureType, GLenum slot) 
{
    /* Cargar textura */
    glGenTextures(1, &ID);
    type = textureType;

    // Se debe asignar el slot antes de enlazar la textura
    glActiveTexture(slot);
    glBindTexture(type, ID);

    // Parametros
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_LINEAR);

    // Ancho, alto y numero de canales de color
    GLint width, height, nrChannels;
    /* 
        stb_image hace la lectura de la imagen desde arriba hacia abajo, mientras que opengl hace la lectura desde abajo hacia arriba
    por lo que hace que la imagen salga invertida. Por lo tanto la siguiente función invierte los datos.
    */
    stbi_set_flip_vertically_on_load(true);
    /* 
        unsigned char == 1 byte, resulta conveniente guardar la información del pixel dentro de un caracter sin signo ya que este ocupa un byte. 
    */
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data) 
    {
        // target, mipmap level, format(store), width, height, (legacy), format(data), datatype and data
        glTexImage2D(type, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);
    }
    else 
    {   
        // No se pudo cargar la imagen
        std::cout << "Couldn't load the image at '" << imagePath << "'." << std::endl;
    }
    // Liberar memoria
    stbi_image_free(data);
}

void Texture::bind() 
{
    glBindTexture(type, ID);
}
void Texture::unbind()
{
    glBindTexture(type, 0);
}