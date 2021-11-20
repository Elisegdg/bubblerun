#include <rendering/Model.hpp>

namespace rendering{


void Model::setVbo(){
    GLuint vbo;
    m_vbo = vbo;
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexCount() * sizeof(glimac::ShapeVertex), getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::setIbo(){
    GLuint ibo;
    m_ibo = ibo;
    m_isIbo = true;
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getVertexCount() * sizeof(int), getIndexPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::setVao(){
    GLuint vao;
    m_vao = vao;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    if(m_isIbo){        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

const glimac::ShapeVertex* Model::getDataPointer() const{
    return &m_vertices[0];
}



const int* Model::getIndexPointer() const{
    return &m_index[0];
}



}