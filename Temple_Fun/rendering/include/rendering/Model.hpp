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

struct Vertex{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoords;

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        :_position(pos), _normal(norm), _texCoords(tex)
    {}
};

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

    void loadModel(const std::string& fileName);
    void setVbo(std::vector<glimac::ShapeVertex> &model);
    void draw_model(rendering::Camera *camera, rendering::ShaderManager &Program, glm::mat4 ProjMatrix)
    {

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0., 1., 10.));
    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(1, 1, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    //Program.uniform1i("uTexture", 0);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES,0,m_vertices.size());

}




};

}

#endif