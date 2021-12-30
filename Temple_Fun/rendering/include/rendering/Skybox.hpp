#ifndef _SKYBOX_HPP
#define _SKYBOX_HPP

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <rendering/Program.hpp>

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
        "../Temple_Fun/assets/textures/underwater/right.png",
        "../Temple_Fun/assets/textures/underwater/left.png",
        "../Temple_Fun/assets/textures/underwater/top.png",
        "../Temple_Fun/assets/textures/underwater/bottom.png",
        "../Temple_Fun/assets/textures/underwater/front.png",
        "../Temple_Fun/assets/textures/underwater/back.png"};

class Skybox
{
private:
    GLuint m_vao;
    GLuint m_vbo;

public:
    
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

    ~Skybox() = default;
    
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



#endif