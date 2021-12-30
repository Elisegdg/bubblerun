#include <GL/glew.h>
#include <iostream>
#include <map>
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
#include <rendering/Text.hpp> 
#include <rendering/Menu.hpp>
#include <rendering/Cursor.hpp>
#include <rendering/json.hpp>
#include <rendering/Score.hpp>
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string.h>

using namespace glimac;
using namespace rendering;
using json = nlohmann::json;


static SDL_Cursor *init_system_cursor(const char *image[])
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for (row=0; row<32; ++row) {
    for (col=0; col<32; ++col) {
      if (col % 8) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (image[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}


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

    SDL_Cursor *cursor = init_system_cursor(arrow);
    SDL_Cursor *cursor2 = init_system_cursor(arrow2);
    
    bool menu_bool = true;
    Menu menu;

    bool menu_score = false;

    bool menu_play_again = false;

    Score scorejson;

    CourseMap courseMap;
    courseMap.loadMap("../Temple_Fun/assets/map.ppm");
    courseMap.loadCoins();
    Player player(courseMap);
    Object *objet = courseMap.findObject(player.getFloorCoord());
    //Object *objet;
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

    ShaderManager menuShader(applicationPath,"shaders/menu.vs.glsl","shaders/menu.fs.glsl");
    menuShader.addUniform("uModelMatrix");
    menuShader.addUniform("uColor");


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

    //VAO et VBO texte
    
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
    int step_turn = 0;
    bool turn_up = false;
    bool turn_down = false;
    bool turn_right = false;
    bool turn_left = false;
    
    bool again= true;

    while (!done)
    {
        
        
        currentTime = SDL_GetTicks();
        glm::mat4 ViewMatrix = camera->getViewMatrix();

        int x;
        int y;
        SDL_GetMouseState(&x,&y);
        //std::cout<<x<<"  "<<y<<std::endl;

        SDL_SetCursor(cursor);
        if(menu_bool & !menu_score & x>764 & y>425 & x<932 & y<467)
        {
            SDL_SetCursor(cursor2);
            

        }
        if(menu_bool & !menu_score & x>764 & y>540 & x<932 & y<583)
        {
            SDL_SetCursor(cursor2);
            

        }
        if (!menu_bool & menu_score & x>1447 & y>789 & x<1613 & y<829)
            {
                SDL_SetCursor(cursor2);            
            }
        

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true;
            }

            if (menu_bool & !menu_score & !menu_play_again & e.type == SDL_MOUSEBUTTONUP & x>764 & y>425 & x<932 & y<467)
            {
                menu_bool =false;
                
            }

            if (menu_play_again & !menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x>764 & y>425 & x<932 & y<467)
            {
                menu_play_again =false;
                
            }
            if (menu_play_again & !menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x>764 & y>540 & x<932 & y<583)
            {
                menu_play_again = false;
                menu_score =true;
                
            }
            
            if (menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x>764 & y>540 & x<932 & y<583)
            {
                menu_score =true;
                menu_bool =false;
                
            }
            if (!menu_bool & menu_score & e.type == SDL_MOUSEBUTTONUP & x>1447 & y>789 & x<1613 & y<829)
            {
                menu_score =false;
                menu_bool =true;
                
            }

            if (windowManager.isKeyPressed(SDLK_ESCAPE))
            {
                menu_bool = true;
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

        if (menu_bool & !menu_score  & !menu_play_again)
        {
            glm::mat4 uModelMatrix;
            glm::mat4 translate_background=glm::translate(uModelMatrix,glm::vec3(0,0,0.5));
            glm::mat4 scale_reset = glm::scale(translate_background,glm::vec3(1,1,1));
            //glm::mat4 translate_bouton_play=glm::translate(uModelMatrix,glm::vec3(0,0,0.5));
            glm::mat4 bouton_play=glm::scale(uModelMatrix,glm::vec3(0.15,0.06,1));
            glm::mat4 translate_bouton_score=glm::translate(uModelMatrix,glm::vec3(0,-0.25,0));
            glm::mat4 bouton_score=glm::scale(translate_bouton_score,glm::vec3(0.15,0.06,1));

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            menuShader.use();

            //fond du menu
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",scale_reset);
            menuShader.uniform3f("uColor",1,1,1);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //bouton play
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",bouton_play);
            menuShader.uniform3f("uColor",0.f, 0.04f, 0.39f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //bouton score
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",bouton_score);
            menuShader.uniform3f("uColor",0.f, 0.04f, 0.39f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //texte
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            text.RenderText(id, Characters, "... BUBBLE RUN ...", 270.0f, 400.0f, 0.8f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters,"play :", 365.0f, 290.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters,"score :", 360.0f, 215.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            glDisable(GL_BLEND);
        }

        if(menu_score & !menu_bool & !menu_play_again)
        {
            glm::mat4 uModelMatrix;
            glm::mat4 translate_background=glm::translate(uModelMatrix,glm::vec3(0,0,0.5));
            glm::mat4 scale_reset = glm::scale(translate_background,glm::vec3(1,1,1));
            glm::mat4 translate_bouton_back=glm::translate(uModelMatrix,glm::vec3(0.8,-0.8,0.3));
            glm::mat4 bouton_back=glm::scale(translate_bouton_back,glm::vec3(-0.1,0.05,1));

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            menuShader.use();

            //fond du menu score
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",scale_reset);
            menuShader.uniform3f("uColor",1,1,1);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //bouton play
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",bouton_back);
            menuShader.uniform3f("uColor",0.f, 0.04f, 0.39f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //texte
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            int first=scorejson.getArray()["score"][0];
            int second = scorejson.getArray()["score"][1];
            int third = scorejson.getArray()["score"][2];
            text.RenderText(id, Characters, "Best scores :", 300.0f, 400.0f, 0.6f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters,"First    " + std::to_string(first), 320.0f, 300.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f), VAO, VBO);
            text.RenderText(id, Characters,"Second   "+std::to_string(second), 320.0f, 250.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f), VAO, VBO);
            text.RenderText(id, Characters,"Third    " +std::to_string(third), 320.0f, 200.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f), VAO, VBO);
            text.RenderText(id, Characters,"Back", 690.0f, 50.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            
            glDisable(GL_BLEND);

        }

        if(menu_play_again & !menu_score & !menu_bool)
        {
            player.setCoord(glm::vec3(1,0,0));
            player.setLife(true);
            player.setOrientation(0);
            camera->rotateLeft(player.getOrientation());
            
            again = true;
            glm::mat4 uModelMatrix;
            score = 0;
            glm::mat4 translate_background=glm::translate(uModelMatrix,glm::vec3(0,0,0.5));
            glm::mat4 scale_reset = glm::scale(translate_background,glm::vec3(1,1,1));
            //glm::mat4 translate_bouton_play=glm::translate(uModelMatrix,glm::vec3(0,0,0.5));
            glm::mat4 bouton_play_again=glm::scale(uModelMatrix,glm::vec3(0.2,0.06,1));
            glm::mat4 translate_bouton_score=glm::translate(uModelMatrix,glm::vec3(0,-0.25,0));
            glm::mat4 bouton_score=glm::scale(translate_bouton_score,glm::vec3(0.15,0.06,1));

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            menuShader.use();

            //fond du menu
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",scale_reset);
            menuShader.uniform3f("uColor",1,1,1);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //bouton play
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",bouton_play_again);
            menuShader.uniform3f("uColor",0.f, 0.04f, 0.39f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //bouton score
            glBindVertexArray(menu.getVaoMenu());
            menuShader.uniformMatrix4fv("uModelMatrix",bouton_score);
            menuShader.uniform3f("uColor",0.f, 0.04f, 0.39f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            //texte
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            text.RenderText(id, Characters, "... BUBBLE RUN ...", 270.0f, 400.0f, 0.8f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters,"play again :", 325.0f, 290.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters,"score :", 360.0f, 215.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            glDisable(GL_BLEND);
        }

            // if (currentTime - previousTime > 5)  // TO DO : set the speed in a variable
        
        if (again = true & !menu_play_again & player.getCoord()==glm::vec3(1,0,0))
        {
            courseMap.loadCoins();
            again=false;
        }
        
        
        if(!menu_bool & !menu_score & !menu_play_again)
        {
            std::cout << "getCoord : " << player.getCoord() << std::endl;
            // GAME LOOP
            if (player.isLife() & player.getCoord()[1] != courseMap.end() & player.getCoord()[0] >= 0 & player.getCoord()[1] >= 0)
            {
                
                objet = courseMap.findObject(player.getFloorCoord());
                
                // std::cout << "getFloorCoord : " << player.getFloorCoord() << std::endl;
                //std::cout << "object : " << objet->getName() << std::endl;
                //std::cout << std::endl;
                if (objet->getIfCoins() & !player.isJumping())
                {
                    objet->removeCoin();
                    score+=50;
                }
                if (objet->getName() == "straight")
                {
                    player.moveside(windowManager, repeat,turn_up, turn_down, turn_right, turn_left);
                    player.setJump(windowManager, repeat);
                }

                if (objet->getName() == "up" & turn_up)
                {
                    std::cout << "object : " << objet->getName() << std::endl;
                    turn_up = false;
                    step_turn =0;
                    player.setCoord(objet->getCoord());
                    player.setOrientation(180.);
                    player.move(glm::vec3(0, -1, 0));
                    camera->rotateLeft(player.getOrientation());
                }

                if (objet->getName() == "down" & turn_down)
                {
                    std::cout << "object : " << objet->getName() << std::endl;
                    turn_down = false;
                    step_turn =0;
                    player.setCoord(objet->getCoord());
                    player.setOrientation(0.);
                    player.move(glm::vec3(0, 1, 0));
                    camera->rotateLeft(player.getOrientation());
                }

                if (objet->getName() == "right" & turn_right)
                {
                    std::cout << "object : " << objet->getName() << std::endl;
                    turn_right = false;
                    step_turn =0;
                    player.setCoord(objet->getCoord());
                    player.setOrientation(90.);
                    player.move(glm::vec3(1, 0, 0));
                    camera->rotateLeft(player.getOrientation());
                }

                if (objet->getName() == "left"  & turn_left)
                {
                    std::cout << "object : " << objet->getName() << std::endl;
                    turn_right = false;
                    step_turn =0;
                    player.setCoord(objet->getCoord());
                    player.setOrientation(-90.);
                    player.move(glm::vec3(-1, 0, 0));
                    camera->rotateLeft(player.getOrientation());
                }

                if (objet->getName() == "empty" & player.getCoord()[2] < 0.3 || player.getCoord().x<0)
                {

                    player.setLife(false);
                    std::cout << "oops, you fell" << std::endl;
                }

                if (objet->getName() == "obstacle" & player.getCoord()[2] < 0.3)
                {
                    player.setLife(false);
                    std::cout << "oops you stumbled over an obstacle" << std::endl;
                }

                if (currentTime - previousTime > 5) // TO DO : set the speed in a variable
                {
                    player.moveOrientation();

                    if (player.isJumping())
                        player.jump(windowManager, repeat, step);

                    if (step >= 10)
                        player.fall(step);

                    if (camera->getCameraType() == 1)
                        camera->moveFront(0.1);

                    if(step_turn<30 & (turn_right || turn_up || turn_down || turn_left) )
                    {
                        step_turn+=1;
                    }
                    if(step_turn>=30)
                    {
                        turn_up = false;
                        turn_down = false;
                        turn_left = false;
                        turn_up = false;
                        step_turn =0;
                    }

                    previousTime = currentTime;
                }
            }
            if (player.isLife()==false)
            {
                std::cout<<"mort"<<std::endl;
                scorejson.addScore(score);
                menu_play_again = true;
            }
            

            if(player.getFloorCoord().y==courseMap.end())
            {
                scorejson.addScore(score);
                menu_play_again = true;
                
            }

            camera->eventCamera(windowManager);
            /*********************************
             *      RENDERING CODE           *
             *********************************/

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // glBindVertexArray(vao);

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
            std::string scorestring = std::to_string(int(score));
            text.RenderText(id, Characters, "BUBBLE RUN", 25.0f, 25.0f, 1.0f, glm::vec3(0.87f, 0.325f, 0.03f), VAO, VBO);
            text.RenderText(id, Characters, "Score : " + scorestring, 650.0f, 570.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f), VAO, VBO);

            
        }
        glDisable(GL_BLEND);
            windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}