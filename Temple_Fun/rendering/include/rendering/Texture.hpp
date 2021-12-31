/**
 * \file Texture.hpp
 * \brief Declaration of the class Texture
*/

#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <iostream>



namespace rendering{
/*! \class Texture
   * \brief Texture manager Class
   *
   *  This class manages the textures
   */
class Texture {

private:
    GLuint m_textureId; /*!< The texture Id */
    std::string m_texturePath; /*!< Texture filepath*/
    std::unique_ptr<glimac::Image> m_textureImage; /*!< Pointer to the texture*/

public:

    /*!
    *  \brief Default Constructor of the Texture class
    */
    Texture():
		m_textureId(0), m_texturePath("")
	{

    }
    
    /*!
     *  \brief Constructor of the Texture class
     * 
     *  \param texutreFile : The filepath of the texture
     * 
     */ 
    Texture(const std::string &textureFile):
        m_textureId(0), 
        m_texturePath(textureFile) 
    {
        loadTexture();
    }

    /*!
     *  \brief Copy constructor of the Texture class
     * 
     *  \param Texture : The texture that needs to be copied
     */ 
    Texture(const Texture& texture):
        m_textureId(0), m_texturePath(texture.m_texturePath) 
    {
        loadTexture();
    }

    /*!
     *  \brief Destructor of the Texture class
     *  Deletes the texture at the end of the program using glDeleteTextures
     */
    ~Texture(){
        glDeleteTextures(1, &m_textureId);
    }

    /*!
     *  \brief Getter of the texture id 
     */
    GLuint getTextureId() const{
        return m_textureId;
    }
    
    /*!
     *  \brief Loads the texture and binds it
     *
     * 
     */
    void loadTexture(){

        m_textureImage = glimac::loadImage(m_texturePath);

        if (m_textureImage == nullptr){
            std::cout<<"Error, texture could not be loaded"<<std::endl; // TO DO : exception
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