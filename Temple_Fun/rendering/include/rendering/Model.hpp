#ifndef _MODEL_HPP
#define _MODEL_HPP

#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <rendering/Texture.hpp>
#include <glimac/common.hpp>


namespace rendering{

class Model{

protected:
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;
    bool m_isIbo = false;
    rendering::Texture m_texture;
    std::vector<glimac::ShapeVertex> m_vertices;
    std::vector<int> m_index;
    GLsizei m_vertexCount;

public:
    
    Model(rendering::Texture texture):
        m_texture(texture)
        {}

    ~Model() = default;

    // METHODS
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

    GLuint getVao(){
        return m_vao;
    }

    GLuint getVbo(){
        return m_vbo;
    }

    GLuint getIbo(){
        return m_vao;
    }

    void setVao();
    void setVbo();
    void setIbo();
    const glimac::ShapeVertex* getDataPointer() const;
    GLsizei getVertexCount() const{
    return m_vertexCount;
}
    const int* getIndexPointer() const;

};

}

#endif