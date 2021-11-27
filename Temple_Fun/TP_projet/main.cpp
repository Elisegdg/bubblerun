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
#include <game/Player.hpp>
#include <game/Object.hpp>

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
    *     INITIALIZATION CODE       *
   *********************************/

    CourseMap map;
    map.loadMap("/home/clara/Documents/Projet/Temple_Fun/assets/test_parcours4.ppm");
    Texture ground("/home/clara/Documents/Projet/Temple_Fun/assets/textures/ground4.png");
    Texture nemo("/home/clara/Documents/Projet/Temple_Fun/assets/textures/nemo.jpg");
    Cube cube_path(ground, 1);
    Cube cube_nemo(nemo, 1);

    TrackballCamera trackball_camera;
    EyesCamera eyes_camera;
    Camera *camera = &eyes_camera;

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

    //Creation of the cube used for the Player and the Path
    cube_path.setVbo();
    cube_path.setIbo();
    cube_path.setVao();

    cube_nemo.setVbo();
    cube_nemo.setIbo();
    cube_nemo.setVao();

    // Application loop:
    bool done = false;

    Player player(map);

    Object *objet = map.findObject(player.getCoord());

    bool right = false;
    bool left = false;
    bool up = false;
    bool down = true;

    while (!done)
    {
        glm::mat4 ViewMatrix = camera->getViewMatrix();
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 2000.f / 1000.f, 0.1f, 100.f);

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
        

        camera->eventCamera(&windowManager);

        /*********************************
         *      RENDERING CODE           *
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);

        TextureProgram.use();

        player.draw(&cube_nemo, camera, &TextureProgram, ProjMatrix);

        // Drawing of the Path
        map.drawMap(&cube_path, camera, &TextureProgram, ProjMatrix, &windowManager);

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

        
        if (player.isLife() & player.getCoord()[1] != map.end())
        {

            objet = map.findObject(player.getCoord());

            std::cout << std::endl;
            std::cout << std::endl;

            std::cout << player.getCoord() << std::endl;

            if (objet->getName() == "straight")
            {
                std::cout << "test2" << std::endl;

                char a = 0;
                std::cout << "q gauche d droite" << std::endl;
                //std::cin >> a;

                if (right == true)
                {
                    if (windowManager.isKeyPressed(SDLK_q))
                    {
                        player.move(glm::vec3(0, 1, 0));
                        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(10., 0.6, 4.));
                    }
                    if (windowManager.isKeyPressed(SDLK_d))
                    {
                        player.move(glm::vec3(0, -1, 0));
                    }
                }

                if (left == true)
                {
                    if (windowManager.isKeyPressed(SDLK_q))
                    {
                        player.move(glm::vec3(0, -1, 0));
                    }
                    if (windowManager.isKeyPressed(SDLK_d))
                    {
                        player.move(glm::vec3(0, 1, 0));
                    }
                }

                if (up == true)
                {
                    if (windowManager.isKeyPressed(SDLK_q))
                    {
                        player.move(glm::vec3(-1, 0, 0));
                    }
                    if (windowManager.isKeyPressed(SDLK_d))
                    {
                        player.move(glm::vec3(1, 0, 0));
                    }
                }

                if (down == true)
                {
                    if (windowManager.isKeyPressed(SDLK_q))
                    {
                        player.move(glm::vec3(1, 0, 0));
                    }
                    if (windowManager.isKeyPressed(SDLK_d))
                    {
                        player.move(glm::vec3(-1, 0, 0));
                    }
                }
            }
            if (objet->getName() == "up")
            {
                up = true;
                right = false;
                left = false;
                down = false;
            }
            if (objet->getName() == "down")
            {
                up = false;
                right = false;
                left = false;
                down = true;
            }

            if (objet->getName() == "right")
            {
                up = false;
                right = true;
                left = false;
                down = false;
            }
            if (objet->getName() == "left")
            {
                up = false;
                right = false;
                left = true;
                down = false;
            }
            if (objet->getName() == "empty")
            {

                player.setLife();
            }

            if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }

            if (windowManager.isKeyPressed(SDLK_z))
            {
                if (right == true)
                {
                    player.move(glm::vec3(1, 0, 0));
                }

                if (left == true)
                {
                    player.move(glm::vec3(-1, 0, 0));
                }

                if (up == true)
                {
                    player.move(glm::vec3(0, -1, 0));
                }

                if (down == true)
                {
                    player.move(glm::vec3(0, 1, 0));
                }
            }
        }

        else
        {
            done = true;
        }
        }
    }

    return EXIT_SUCCESS;
}