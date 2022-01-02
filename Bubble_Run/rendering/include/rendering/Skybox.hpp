/**
 * \file Skybox.hpp
 * \brief Declaration of the class Skybox
*/

#ifndef _SKYBOX_HPP
#define _SKYBOX_HPP

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <rendering/Program.hpp>

namespace rendering{
float skyboxVertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

std::vector<std::string> skybox_sky =
    {
        "../Bubble_Run/assets/textures/underwater/right.png",
        "../Bubble_Run/assets/textures/underwater/left.png",
        "../Bubble_Run/assets/textures/underwater/top.png",
        "../Bubble_Run/assets/textures/underwater/bottom.png",
        "../Bubble_Run/assets/textures/underwater/front.png",
        "../Bubble_Run/assets/textures/underwater/back.png"};

/*! \class Skybox
   * \brief Class of Skybox
   *
   *  This class allows to create and draw the skybox. 
   * The hpp file also contains the path to the textures and the vertices.
   */
class Skybox
{
private:
    GLuint m_vao; /*!< vao of the skybox*/
    GLuint m_vbo; /*!< vbo of the skybox*/

public:
    
    /*!
    *  \brief Constructor of the Skybox
    *  It initializes and binds the buffers
    */
    Skybox()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    }

    /*!
    *  \brief Destructor of the Skybox
    *  It deletes the buffers
    */
    ~Skybox(){
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }
    
    /*!
    *  \brief Drawing of the Skybox
    *  \param SkyboxProgram The shader of the skybox
    *  \param camera The camera to get the view matrix
    *  \param ProjMatrix The Projection Matrix
    *  \param cubemapTexture The texture
    */
    void draw(rendering::ShaderManager& SkyboxProgram, rendering::Camera* camera, glm::mat4 &ProjMatrix, unsigned int cubemapTexture)
    {
        glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));

        SkyboxProgram.uniformMatrix4fv("projection", ProjMatrix);
        SkyboxProgram.uniformMatrix4fv("view", skyboxViewMatrix);

        glBindVertexArray(m_vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        SkyboxProgram.uniform1i("uSkybox", 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
};

}

#endif