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
#include <rendering/Text.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string.h>

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
    Object *objet = courseMap.findObject(player.getFloorCoord());
    double score = 0;

    TrackballCamera trackball_camera(&player);
    EyesCamera eyes_camera(&player);
    Camera *camera = &trackball_camera;

    Texture obstacle("../Temple_Fun/assets/textures/ground.png");
    Texture nemo("../Temple_Fun/assets/textures/nemo.jpg");
    Texture ground("../Temple_Fun/assets/textures/stone_ground.png");
    Texture coin("../Temple_Fun/assets/textures/gold.png");

    unsigned int VAO, VBO;
    std::map<char, Text> Characters;
    Text text;
    text.loadFont(Characters);

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

    ShaderManager TextProgram(applicationPath, "shaders/text.vs.glsl", "shaders/text.fs.glsl");
    TextProgram.addUniform("projection");

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    TextProgram.use();
    glUniformMatrix4fv(glGetUniformLocation(TextProgram.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);

    
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
                    camera->rotateLeft(player.getOrientation());
                }
                else
                {
                    camera = &trackball_camera;
                    camera->rotateLeft(player.getOrientation());
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
            
            objet = courseMap.findObject(player.getFloorCoord()); 
            std::cout<<"getCoord : "<<player.getCoord()<<std::endl;
            std::cout<<"getFloorCoord : "<<player.getFloorCoord()<<std::endl;
            std::cout<<"object : "<<objet->getName()<<std::endl;
            std::cout<<std::endl;
            if(objet->getIfCoins() & !player.isJumping()){
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
            
            if (objet->getName() == "empty" & player.getCoord()[2]<0.3 )
            {

                player.setLife();
                std::cout<<"oops, you fell"<<std::endl;
            }

            if (objet->getName() == "obstacle" & player.getCoord()[2]<0.3)
            {
                player.setLife();
                std::cout<<"oops you stumbled over an obstacle"<<std::endl;
            }

            



            if (currentTime - previousTime > 5)  // TO DO : set the speed in a variable
            {
                player.moveOrientation();

                if (player.isJumping())    player.jump(windowManager, repeat, step);
                

                if (step>=10)   player.fall(step);
            

                if (camera->getCameraType() == 1)
                    camera->moveFront(0.1);

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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        TextProgram.use();
        GLuint id = TextProgram.getId();
        std::string scorestring=std::to_string(int(score));
        text.RenderText(id,Characters, "BUBBLE RUN", 25.0f, 25.0f, 1.0f, glm::vec3(0.87f, 0.325f, 0.03f),VAO,VBO);
        text.RenderText(id,Characters, "Score : "+scorestring, 650.0f, 570.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f),VAO,VBO);

        glDisable(GL_BLEND);
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}