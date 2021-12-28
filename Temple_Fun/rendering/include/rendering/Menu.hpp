#pragma one

#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <glimac/common.hpp>

class Menu
{
private:
    GLuint m_vbo;
    GLuint m_vao;
    std::vector<glimac::Vertex2DColor> m_vertices;
public:
    
    Menu();
    GLuint getVaoMenu(){return m_vao;}
    

};


Menu::Menu()
{
    //Création d'un VBO
    glGenBuffers(1, &m_vbo);

    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    //Création d'un tableau de float pour stocker les points du VBO
    //On utilise la structure nouvellement créée
    m_vertices = {
        glimac::Vertex2DColor(glm::vec3(-1., -1.,1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., -1.,1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(-1., 1.,1), glm::vec3(1, 1, 1)),

        glimac::Vertex2DColor(glm::vec3(-1., 1.,1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., 1.,1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., -1.,1), glm::vec3(1, 1, 1))
    };
    //Puis on envois les données à la CG
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(glimac::Vertex2DColor), m_vertices.data(), GL_STATIC_DRAW);

    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Création du VAO
    glGenVertexArrays(1, &m_vao);

    //Binding du vao (un seul à la fois)
    glBindVertexArray(m_vao);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    //Indiquer à OpenGL où trouver les sommets
    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //Spécification du format de l'attribut de sommet position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DColor), (const GLvoid*)offsetof(glimac::Vertex2DColor, position));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DColor), (const GLvoid*)offsetof(glimac::Vertex2DColor, color));
    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Débindind du vao de la cible pour éviter de le remodifier
    glBindVertexArray(0);
}

