#include "glimac/Image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <GL/glew.h>


namespace glimac {


std::unique_ptr<Image> loadImage(const FilePath& filepath) {
    int x, y, n;
    unsigned char *data = stbi_load(filepath.c_str(), &x, &y, &n, 4);
    if(!data) {
        return std::unique_ptr<Image>();
    }
    std::unique_ptr<Image> pImage(new Image(x, y));
    unsigned int size = x * y;
    auto scale = 1.f / 255;
    auto ptr = pImage->getPixels();
    for(auto i = 0u; i < size; ++i) {
        auto offset = 4 * i;
        ptr->r = data[offset] * scale;
        ptr->g = data[offset + 1] * scale;
        ptr->b = data[offset + 2] * scale;
        ptr->a = data[offset + 3] * scale;
        ++ptr;
    }
    stbi_image_free(data);
    return pImage;
}

std::unordered_map<FilePath, std::unique_ptr<Image>> ImageManager::m_ImageMap;

const Image* ImageManager::loadImage(const FilePath& filepath) {
    auto it = m_ImageMap.find(filepath);
    if(it != std::end(m_ImageMap)) {
        return (*it).second.get();
    }
    auto pImage = glimac::loadImage(filepath);
    if(!pImage) {
        return nullptr;
    }
    auto& img = m_ImageMap[filepath] = std::move(pImage);
    return img.get();
}


unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            throw std::string("Cubemap texture failed to load at path "+ faces[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

}