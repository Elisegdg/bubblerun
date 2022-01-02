#include <rendering/Model.hpp>
#include <glimac/common.hpp>


#define TINYOBJLOADER_IMPLEMENTATION
#include <glimac/tiny_obj_loader.h>

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

void Model::setBuffers() {
    setVbo();
    setIbo();  
    setVao();
}

const glimac::ShapeVertex* Model::getDataPointer() const{
    return &m_vertices[0];
}



const int* Model::getIndexPointer() const{
    return &m_index[0];
}

void Model::loadModel(const std::string& fileName){
        
        // Load 3D object
        std::string inputfile = "../Bubble_Run/assets/models/"+fileName;
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials; 
        
        std::string warn;
        std::string err;
        bool ret = tinyobj::LoadObj(&attrib,&shapes,&materials, &warn, &err, inputfile.c_str(), nullptr);
        
        if (!err.empty()) { // `err` may contain warning message.
            std::cerr << err << std::endl;
        }

        if (!ret) {
            exit(1);
        }

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {

                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    // access to vertex
                    glimac::ShapeVertex newVertex = glimac::ShapeVertex(
                        
                        // POSITION
                        glm::vec3(
                            tinyobj::real_t(attrib.vertices[3*size_t(idx.vertex_index)+0]),
                            tinyobj::real_t(attrib.vertices[3*size_t(idx.vertex_index)+1]),
                            tinyobj::real_t(attrib.vertices[3*size_t(idx.vertex_index)+2])
                        ),

                        // NORMAL
                        glm::vec3(
                            tinyobj::real_t(attrib.normals[3*size_t(idx.normal_index)+0]),  // nx
                            tinyobj::real_t(attrib.normals[3*size_t(idx.normal_index)+1]),  // ny
                            tinyobj::real_t(attrib.normals[3*size_t(idx.normal_index)+2])   // nz
                        ),

                        // TEXTURE_COORDINATES
                        glm::vec2(
                            tinyobj::real_t(attrib.texcoords[2*size_t(idx.texcoord_index)+0]),  //tx
                            tinyobj::real_t(attrib.texcoords[2*size_t(idx.texcoord_index)+1])   //ty
                        )
                    );

                    m_vertices.push_back(newVertex);
                }
                index_offset += fv;
            }
        }
        m_vertexCount = m_vertices.size();
}

}