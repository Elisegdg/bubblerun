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

using namespace glimac;
using namespace rendering;

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1700, 900, "Temple_Fun");
    int previousTime = 0, currentTime = 0;

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

    CourseMap courseMap;
    courseMap.loadMap("/home/clara/Documents/Projet/Temple_Fun/assets/map.ppm");
    Player player(courseMap);
    Object *objet = courseMap.findObject(player.getCoord());

    TrackballCamera trackball_camera(&player);
    EyesCamera eyes_camera(&player);
    Camera *camera = &trackball_camera;

    Texture obstacle("/home/clara/Documents/Projet/Temple_Fun/assets/textures/ground.png");
    Texture nemo("/home/clara/Documents/Projet/Temple_Fun/assets/textures/nemo.jpg");
    Texture ground("/home/clara/Documents/Projet/Temple_Fun/assets/textures/stone_ground.png");
    Texture coin("/home/clara/Documents/Projet/Temple_Fun/assets/textures/gold.png");


    Cube cube_path(ground, 1);
    Cube cube_nemo(nemo, 1);
    Cube cube_obstacle(obstacle, 1);
    Cube cube_coin(coin, 1);

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

    cube_coin.setVbo();
    cube_coin.setIbo();
    cube_coin.setVao();

    cube_obstacle.setVbo();
    cube_obstacle.setIbo();
    cube_obstacle.setVao();

    // Application loop:
    bool done = false;
    bool repeat = false;
    int step = 0;
    while (!done)
    {
        currentTime = SDL_GetTicks();
        glm::mat4 ViewMatrix = camera->getViewMatrix();

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true;
            }

            // CAMERA SWITCH AND LOCK
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

            if (windowManager.isKeyPressed(SDLK_l))
            {
                camera->setLocker();
            }
            
            // PREVENT THE EVENT FROM REPEATING OUTSIDE POLLEVENT
            if (windowManager.isKeyPressed(SDLK_d))
            {
                repeat = true;
            }

            if (windowManager.isKeyPressed(SDLK_q))
            {
                repeat = true;
            }

            if (windowManager.isKeyPressed(SDLK_z))
            {
                repeat = true;
            }
        }


        //GAME LOOP
        if (player.isLife() & player.getCoord()[1] != courseMap.end() & player.getCoord()[0] >= 0 & player.getCoord()[1] >= 0)
        {
            
            objet = courseMap.findObject(player.getCoord()); 
            if(objet->getIfCoins()){
                objet->removeCoin();
            }
            if (objet->getName() == "straight")
            {
                player.moveside(windowManager, repeat);
                player.setJump(windowManager,repeat);
            }

            if (objet->getName() == "up")
            {
                player.setOrientation(180.);
                camera->rotateLeft(player.getOrientation());
            }

            if (objet->getName() == "down")
            {
                player.setOrientation(0.);
                camera->rotateLeft(player.getOrientation());
            }

            if (objet->getName() == "right")
            {
                player.setOrientation(90.);
                camera->rotateLeft(player.getOrientation());
            }

            if (objet->getName() == "left")
            {
                player.setOrientation(-90.);
                camera->rotateLeft(player.getOrientation());

                
            }
            
            if (objet->getName() == "empty")
            {

                player.setLife();
            }

            if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }

            



            if (currentTime - previousTime > 100)  // TO DO : set the speed in a variable
            {
                player.moveOrientation();

                if (player.isJumping())    player.jump(windowManager, repeat, step);
                

                if (step>1)   player.fall(step);
            

                if (camera->getCameraType() == 1)
                    camera->moveFront(1);

                previousTime = currentTime;
            }
            
        }

        else
        {
            done = true;
        }

        camera->eventCamera(windowManager);
        /*********************************
        *      RENDERING CODE           *
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glBindVertexArray(vao);

        TextureProgram.use();

        // Drawing of the hero as a cube
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 1700.f / 900.f, 0.1f, 100.f);

        player.draw(cube_nemo, camera, TextureProgram, ProjMatrix);

        // Drawing of the Path
        courseMap.drawMap(cube_path, cube_coin, camera, TextureProgram, ProjMatrix, windowManager);
        courseMap.drawObstacle(cube_obstacle, camera, TextureProgram, ProjMatrix, windowManager);

        // Drawing of the Skybox
        glDepthFunc(GL_LEQUAL); 
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