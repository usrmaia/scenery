#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdio.h>

void Texture::load(const char *file_path){
    stbi_set_flip_vertically_on_load(true);
    this->date = stbi_load(file_path, &this->width, &this->height, &this->canals, 0);

    if(!this->date) printf("Erro in load texture!\n");
    
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGB, this->width, this->height,
                0, GL_RGB, GL_UNSIGNED_BYTE, this->date);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(this->date);
}

unsigned int Texture::get_id(){
    return this->id;
}