//
// Created by TANK1_41 on 4/1/2022.
//

#include <iostream>
#include "textures.h"
#include "GL/glew.h"
#include "stb_image/stb_image.h"

unsigned int texture::s_slot{0};

texture::texture(const char *fileLocation, unsigned int colorFormat)
        : m_renderID(NULL) {
    // texture 1
    // ---------
    glGenTextures(1, &m_renderID);
    glBindTexture(GL_TEXTURE_2D, m_renderID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char *data = stbi_load(fileLocation, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    m_position = s_slot;
    s_slot++;
}

void texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + m_position);
    glBindTexture(GL_TEXTURE_2D, m_renderID);
}

void texture::unBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int texture::getRenderID() const {
    return m_renderID;
}
