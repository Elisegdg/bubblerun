#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <iostream>



namespace rendering{

class Texture {

private:
    GLuint m_textureId; 
    std::string m_texturePath; 
    std::unique_ptr<glimac::Image> m_textureImage; 

public:
	// Constructors
    Texture():
		m_textureId(0), m_texturePath("")
	{

    }
    
    Texture(const std::string &textureFile):
        m_textureId(0), 
        m_texturePath(textureFile) 
    {
        try{
            loadTexture();
        }
        catch(const std::string &s){
            std::cerr<<"Error : "<<s<<std::endl;
        }
    }

    Texture(const Texture& texture):
        m_textureId(0), m_texturePath(texture.m_texturePath) 
    {
        try{
            loadTexture();
        }
        catch(const std::string &s){
            std::cerr<<"Error : "<<s<<std::endl;
        }
    }

    // Destructor
    ~Texture(){}

    // Methods
    GLuint getTextureId() const{
        return m_textureId;
    }
    
    void loadTexture(){

        m_textureImage = glimac::loadImage(m_texturePath);

        if (m_textureImage == nullptr){
            throw std::string("Texture could not be loaded at " + m_texturePath); // TO DO : exception
        }

        glGenTextures(1, &m_textureId);
        
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureImage->getWidth(), m_textureImage->getHeight(), 0, GL_RGBA, GL_FLOAT, m_textureImage->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
};


}



#endif