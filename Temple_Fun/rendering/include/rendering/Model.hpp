/**
 * \file Model.hpp
 * \brief Declaration of the class Modeel
*/

#ifndef _MODEL_HPP
#define _MODEL_HPP

#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <rendering/Texture.hpp>
#include <glimac/common.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>


namespace rendering{

/*! \class Model
   * \brief Class of Model
   *
   *  This class enables to create meshes
   */
class Model{

protected:
    GLuint m_vbo; /*!< vbo of the model*/
    GLuint m_vao; /*!< vao of the model*/
    GLuint m_ibo; /*!< ibo of the model*/
    bool m_isIbo = false; /*!< Boolean that shows if there is an ibo or not */
    rendering::Texture m_texture; /*!< texture of the model*/
    std::vector<glimac::ShapeVertex> m_vertices; /*!< Vector that contains the vertices (position, texture, normals) */
    std::vector<int> m_index; /*!< Number of indices to draw */
    GLsizei m_vertexCount; /*!< Number of vertices to draw */

public:
    
    /*!
    *  \brief Constructor of the Model class
    *  \param texture The texture of the model
    */
    Model(rendering::Texture texture):
        m_texture(texture)
        {}
    Model() = default;
    
    /*!
    *  \brief Destructor of the Model class
    * Deletes the buffers
    */

    ~Model(){
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    };

    /*!
    *  \brief Draw the model
    */
    void draw(){
        glBindVertexArray(m_vao);
        glBindTexture(GL_TEXTURE_2D, m_texture.getTextureId());
        if(m_isIbo){
            glDrawElements(GL_TRIANGLES, getVertexCount(), GL_UNSIGNED_INT,0);
        }
        else{
            glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
        }
}

    /*!
    *  \brief Getter of the vao of the model
    */
    GLuint getVao() const{
        return m_vao;
    }

    /*!
    *  \brief Getter of the vbo of the model
    */
    GLuint getVbo() const {
        return m_vbo;
    }

    /*!
    *  \brief Getter of the ibo of the model
    */
    GLuint getIbo() const{
        return m_vao;
    }

    /*!
    *  \brief Set and bind the vao 
    */
    void setVao();
    /*!
    *  \brief Set and bind the vbo 
    */
    void setVbo();
    /*!
    *  \brief Set and bind the ibo 
    */
    void setIbo();

    /*!
    *  \brief Set the buffers
    */
    void setBuffers();

    const glimac::ShapeVertex* getDataPointer() const;

    /*!
    *  \brief Getter of the number of vertices
    */
    GLsizei getVertexCount() const{
    return m_vertexCount;
    }


    const int* getIndexPointer() const;

    /*!
    *  \brief .obj file loader with TinyObj
    *  \param fileName Name of the .obj file
    */
    void loadModel(const std::string& fileName);



};

}

#endif