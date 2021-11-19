#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>
#include <rendering/Camera.hpp>
#include <rendering/TrackballCamera.hpp>
#include <rendering/EyesCamera.hpp>
#include <rendering/Texture.hpp>
#include <rendering/Program.hpp>
#include <rendering/Skybox.hpp>
#include <rendering/Cube.hpp>
#include <game/CourseMap.hpp>

using namespace glimac;
using namespace rendering;

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(2000, 1000, "Temple_Fun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    //Parcours map;
    //map.loadMap("/home/clara/Documents/Projet/Temple_Fun/assets/test_parcours.ppm");
    Texture ground("/home/clara/Documents/Projet/Temple_Fun/assets/textures/ground4.png");
    Texture nemo("/home/clara/Documents/Projet/Temple_Fun/assets/textures/nemo.jpg");
    Cube2 cube_path(ground,1);
    Cube2 cube_nemo(nemo, 1);

    TrackballCamera trackball_camera;
    EyesCamera eyes_camera;
    Camera *camera = &eyes_camera;

    struct SkyboxProgram{
    Program m_Program;

    GLint projection;
    GLint view;
    //GLint uNormalMatrix;
    GLint uSkybox;

    SkyboxProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/skybox.vs.glsl",
                              applicationPath.dirPath() + "shaders/skybox.fs.glsl")) {

        projection = glGetUniformLocation(m_Program.getGLId(), "projection");
        view = glGetUniformLocation(m_Program.getGLId(), "view");
        uSkybox = glGetUniformLocation(m_Program.getGLId(), "uSkybox");
        }
};

    // Shaders loading
    FilePath applicationPath(argv[0]);
    
    ShaderManager TextureProgram(applicationPath, "shaders/3D.vs.glsl", "shaders/tex3D.fs.glsl");
    TextureProgram.addUniform("uMVPMatrix");
    TextureProgram.addUniform("uMVMatrix");
    TextureProgram.addUniform("uNormalMatrix");
    TextureProgram.addUniform("uTexture");

    ShaderManager SkyboxProgram(applicationPath, "shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl");
    SkyboxProgram.addUniform("projection");
    SkyboxProgram.addUniform("view");
    SkyboxProgram.addUniform("uSkybox");


    glEnable(GL_DEPTH_TEST);

    // Creation of the Skybox
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    unsigned int cubemapTexture = loadCubemap(skybox_sky);

    // Creation of the Path
    /*GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount() * sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.getVertexCount() * sizeof(int), cube.getIndexPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);*/
    cube_path.setVbo();
    cube_path.setIbo();
    cube_path.setVao();

    cube_nemo.setVbo();
    cube_nemo.setIbo();
    cube_nemo.setVao();

    // Application loop:
    bool done = false;
    while (!done)
    {

        glm::mat4 ViewMatrix = camera->getViewMatrix();

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; 
            }
            if (windowManager.isKeyPressed(SDLK_c))
            {
                if (camera->getCameraType() == 0)
                {
                    camera = &eyes_camera;
                }
                else
                {
                    camera = &trackball_camera;
                }
            }
        }
        glm::ivec2 mousePos_trackball = windowManager.getMousePosition();
        glm::ivec2 mousePos_eyes = glm::ivec2(0.0);

        // Event TrackBallCamera
        if (camera->getCameraType() == 0)
        {
            if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT))
            {
                trackball_camera.moveFront(0.03);
            }
            else if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
                trackball_camera.moveFront(-0.03);

            trackball_camera.rotateLeft(mousePos_trackball.y);
            trackball_camera.rotateUp(mousePos_trackball.x);
        }

        //Event EyesCamera
        else
        {
            if (windowManager.isKeyPressed(SDLK_s))
                camera->moveFront(-0.1);
            if (windowManager.isKeyPressed(SDLK_z))
                camera->moveFront(0.1);
            if (windowManager.isKeyPressed(SDLK_q))
                camera->moveLeft(0.1);
            if (windowManager.isKeyPressed(SDLK_d))
                camera->moveLeft(-0.1);
            if (windowManager.isKeyPressed(SDLK_i))
                camera->rotateLeft(0.2);
            if (windowManager.isKeyPressed(SDLK_k))
                camera->rotateUp(0.2);

            if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
            {
                mousePos_eyes = windowManager.getMousePosition();
                float mousePosX = mousePos_eyes.x / 2000.0f - 0.5;
                float mousePosY = mousePos_eyes.y / 1000.0f - 0.5;

                camera->rotateLeft(-3 * mousePosX);
                camera->rotateUp(-3 * mousePosY);
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);

        TextureProgram.use();

        // Drawing of the hero as a cube
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 2000.f / 1000.f, 0.1f, 100.f);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 1.2, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

        /*glUniformMatrix4fv(pathProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix));
        glUniformMatrix4fv(pathProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glUniformMatrix4fv(pathProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        */
       TextureProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
       TextureProgram.uniformMatrix4fv("uMVMatrix", ViewMatrix);
       TextureProgram.uniformMatrix4fv("uNormalMatrix", NormalMatrix);


        //glDrawElements(GL_TRIANGLES, cube.getVertexCount(), GL_UNSIGNED_INT, 0);
        cube_nemo.draw();

        // Drawing of the path
        for (int i = -1; i <= 1; i++)
        {
            for (int j = 0; j <= 25; j++)
            {
                glm::mat4 newViewMatrix = camera->getViewMatrix();
                newViewMatrix = glm::translate(newViewMatrix, glm::vec3(i, 0,  j));
                newViewMatrix = glm::scale(newViewMatrix, glm::vec3(1, 0.2, 1));
                glm::mat4 newNormalMatrix = glm::transpose(glm::inverse(newViewMatrix));

                //animation of the path
                newViewMatrix = glm::translate(newViewMatrix, glm::vec3(0, 0, -3 * windowManager.getTime()));

                /*glUniformMatrix4fv(pathProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * newViewMatrix));
                glUniformMatrix4fv(pathProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(newViewMatrix));
                glUniformMatrix4fv(pathProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(newNormalMatrix));
                */
                TextureProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * newViewMatrix);
                TextureProgram.uniformMatrix4fv("uMVMatrix", newViewMatrix);
                TextureProgram.uniformMatrix4fv("uNormalMatrix", newNormalMatrix);
                

                
                //glBindTexture(GL_TEXTURE_2D, ground.getTextureId());
                //glUniform1i(pathProgram.uTexture, 0);
                TextureProgram.uniform1i("uTexture",0);
                
                //glDrawElements(GL_TRIANGLES, cube.getVertexCount(), GL_UNSIGNED_INT, 0);
                cube_path.draw();

            }
        }

        // Drawing of the Skybox
        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        SkyboxProgram.use();
        glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
        SkyboxProgram.uniformMatrix4fv("projection", ProjMatrix);
        SkyboxProgram.uniformMatrix4fv("view", skyboxViewMatrix);
        

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        SkyboxProgram.uniform1i("uSkybox", 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
