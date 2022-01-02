/**
 * \file Menu.hpp
 * \brief Declaration of the class Menu
*/

#ifndef _MENU_HPP
#define _MENU_HPP

#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <glimac/common.hpp>

namespace rendering{
/*! \class Menu
   * \brief Game Menus manager
   */
class Menu
{
private:
    GLuint m_vbo; /*!< vbo of the Menu*/
    GLuint m_vao; /*!< vao of the Menu*/
    std::vector<glimac::Vertex2DColor> m_vertices; /*!< Vertices to draw */

public:
    /*!
     *  \brief Constructor of the Menu class

     */

    Menu();

    /*!
     *  \brief Destructor of the Menu class

     */
    ~Menu()=default;

    /*!
     *  \brief Set the main menu
     *
     *  \param windowManager : the SDLWindowManager
     * 
     */
    void setMenuBool(rendering::ShaderManager &menuShader);

    /*!
     *  \brief Set the score menu
     *
     *  \param windowManager : the SDLWindowManager
     * 
     */
    void setMenuScore(rendering::ShaderManager &menuShader);
    
    /*!
     *  \brief Set the "Play Again" menu
     *
     *  \param windowManager : the SDLWindowManager
     * 
     */
    void setMenuPlayAgain(rendering::ShaderManager &menuShader);

    /*!
     *  \brief Getter of the vao  
     */
    GLuint getVaoMenu() { return m_vao; }
};


Menu::Menu()
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_vertices = {
        glimac::Vertex2DColor(glm::vec3(-1., -1., 1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., -1., 1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(-1., 1., 1), glm::vec3(1, 1, 1)),

        glimac::Vertex2DColor(glm::vec3(-1., 1., 1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., 1., 1), glm::vec3(1, 1, 1)),
        glimac::Vertex2DColor(glm::vec3(1., -1., 1), glm::vec3(1, 1, 1))};
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glimac::Vertex2DColor), m_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DColor), (const GLvoid *)offsetof(glimac::Vertex2DColor, position));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Vertex2DColor), (const GLvoid *)offsetof(glimac::Vertex2DColor, color));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Menu::setMenuBool(rendering::ShaderManager &menuShader)
{
    glm::mat4 uModelMatrix;
    glm::mat4 translate_background = glm::translate(uModelMatrix, glm::vec3(0, 0, 0.5));
    glm::mat4 scale_reset = glm::scale(translate_background, glm::vec3(1, 1, 1));
    glm::mat4 bouton_play = glm::scale(uModelMatrix, glm::vec3(0.15, 0.06, 1));
    glm::mat4 translate_bouton_score = glm::translate(uModelMatrix, glm::vec3(0, -0.25, 0));
    glm::mat4 bouton_score = glm::scale(translate_bouton_score, glm::vec3(0.15, 0.06, 1));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menuShader.use();

    // Background
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", scale_reset);
    menuShader.uniform3f("uColor", 1, 1, 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Play Button
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", bouton_play);
    menuShader.uniform3f("uColor", 0.f, 0.04f, 0.39f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Score Button
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", bouton_score);
    menuShader.uniform3f("uColor", 0.f, 0.04f, 0.39f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void Menu::setMenuScore(rendering::ShaderManager &menuShader)
{
    glm::mat4 uModelMatrix;
    glm::mat4 translate_background = glm::translate(uModelMatrix, glm::vec3(0, 0, 0.5));
    glm::mat4 scale_reset = glm::scale(translate_background, glm::vec3(1, 1, 1));
    glm::mat4 translate_bouton_back = glm::translate(uModelMatrix, glm::vec3(0.8, -0.8, 0.3));
    glm::mat4 bouton_back = glm::scale(translate_bouton_back, glm::vec3(-0.1, 0.05, 1));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menuShader.use();

    // Score Background
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", scale_reset);
    menuShader.uniform3f("uColor", 1, 1, 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Play Button
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", bouton_back);
    menuShader.uniform3f("uColor", 0.f, 0.04f, 0.39f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Menu::setMenuPlayAgain(rendering::ShaderManager &menuShader)
{
    
    glm::mat4 uModelMatrix;

    glm::mat4 translate_background = glm::translate(uModelMatrix, glm::vec3(0, 0, 0.5));
    glm::mat4 scale_reset = glm::scale(translate_background, glm::vec3(1, 1, 1));
    glm::mat4 bouton_play_again = glm::scale(uModelMatrix, glm::vec3(0.2, 0.06, 1));
    glm::mat4 translate_bouton_score = glm::translate(uModelMatrix, glm::vec3(0, -0.25, 0));
    glm::mat4 bouton_score = glm::scale(translate_bouton_score, glm::vec3(0.15, 0.06, 1));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menuShader.use();

    //Background
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", scale_reset);
    menuShader.uniform3f("uColor", 1, 1, 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    //Play Button
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", bouton_play_again);
    menuShader.uniform3f("uColor", 0.f, 0.04f, 0.39f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    //Score Button
    glBindVertexArray(getVaoMenu());
    menuShader.uniformMatrix4fv("uModelMatrix", bouton_score);
    menuShader.uniform3f("uColor", 0.f, 0.04f, 0.39f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
}
#endif