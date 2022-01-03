#include <GL/glew.h>
#include <iostream>
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string.h>


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
#include <rendering/Model.hpp>
#include <rendering/Cursor.hpp>
#include <rendering/json.hpp>
#include <rendering/Score.hpp>
#include <rendering/Light.hpp>
#include <rendering/Model.hpp>

#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>


using json = nlohmann::json;


int main(int argc, char **argv)
{

    // Initialize SDL and open a window
    glimac::SDLWindowManager windowManager(1700, 900, "Bubble_Run");
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

    // Menu initialization
    SDL_Cursor *cursor = init_system_cursor(arrow), *cursor2 = init_system_cursor(arrow2);
    rendering::Menu menu;
    bool menu_bool = true, menu_score = false, menu_play_again = false;
    rendering::Score scorejson;

    // Map and game initialization
    game::CourseMap courseMap;
    try
    {
        courseMap.loadMap("../Bubble_Run/assets/map/map70.ppm");
    }
    catch (std::string &s)
    {
        std::cerr << "Error : " << s << std::endl;
    }
    courseMap.loadCoins();
    game::Player player(courseMap, glm::vec3(2, 3, 0)), enemy(courseMap, glm::vec3(2, 0, 0));
    game::Object *objet = courseMap.findObject(player.getFloorCoord());
    game::Object *objet_enemy = courseMap.findObject(enemy.getFloorCoord());
    int score = 0;
    int speed = 5;

    //Rendering initialization

    //Camera initialization
    rendering::TrackballCamera trackball_camera(&player);
    rendering::EyesCamera eyes_camera(&player);
    rendering::Camera *camera = &trackball_camera;

    //Textures and mesh initialization
    rendering::Texture obstacle("../Bubble_Run/assets/textures/ground.png");
    rendering::Texture nemo("../Bubble_Run/assets/models/TEX_Nemo_low.png");
    rendering::Texture ground("../Bubble_Run/assets/textures/stone_ground.png");
    rendering::Texture coin("../Bubble_Run/assets/models/Crystal.png");
    rendering::Texture shark("../Bubble_Run/assets/models/TEX_Squirt_Low.png");

    rendering::Cube cube_path(ground, 1),cube_obstacle(obstacle, 1);
    rendering::Model nemo_obj(nemo);
    rendering::Model shark_obj(shark);

    nemo_obj.loadModel("Nemo.obj");
    nemo_obj.setVbo();
    nemo_obj.setVao();

    cube_path.setBuffers();
    cube_obstacle.setBuffers();

    shark_obj.loadModel("Squirt_LD.obj");
    shark_obj.setVbo();
    shark_obj.setVao();

    rendering::Model coin_obj(coin);
    coin_obj.loadModel("Gem.obj");
    coin_obj.setVbo();
    coin_obj.setVao();

    rendering::Light light;

    std::map<char, rendering::Text> Characters;
    rendering::Text text;
    text.loadFont(Characters);
    text.display();

    // Shaders loading
    glimac::FilePath applicationPath(argv[0]);
    rendering::ShaderManager menuShader(applicationPath, "shaders/menu.vs.glsl", "shaders/menu.fs.glsl");
    menuShader.addUniform("uModelMatrix");
    menuShader.addUniform("uColor");


    rendering::ShaderManager SkyboxProgram(applicationPath, "shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl");
    SkyboxProgram.addUniform("projection");
    SkyboxProgram.addUniform("view");
    SkyboxProgram.addUniform("uSkybox");

    rendering::ShaderManager LightProgram(applicationPath, "shaders/3D.vs.glsl", "shaders/multipleLights.fs.glsl");
    LightProgram.addUniform("uKdiffuseD");
    LightProgram.addUniform("uKspecularD");
    LightProgram.addUniform("uKdiffuseP");
    LightProgram.addUniform("uKspecularP");
    LightProgram.addUniform("uShininess");
    LightProgram.addUniform("uLightDir_vs");
    LightProgram.addUniform("uLightPos_vs");
    LightProgram.addUniform("uLightIntensity");
    LightProgram.addUniform("uLightIntensityPonctual");
    LightProgram.addUniform("uMVPMatrix");
    LightProgram.addUniform("uMVMatrix");
    LightProgram.addUniform("uNormalMatrix");
    LightProgram.addUniform("uTexture");

    rendering::ShaderManager TextProgram(applicationPath, "shaders/text.vs.glsl", "shaders/text.fs.glsl");
    TextProgram.addUniform("projection");

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    TextProgram.use();
    glUniformMatrix4fv(glGetUniformLocation(TextProgram.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);


    // Creation of the Skybox
    rendering::Skybox skybox;
    unsigned int cubemapTexture;
    try
    {
        cubemapTexture = glimac::loadCubemap(rendering::skybox_sky);
    }
    catch (std::string &s)
    {
        std::cerr << "Error : " << s << std::endl;
    }


    // Application loop:
    bool done = false, repeat = false, again = true;
    int step = 0, step_turn = 0;
    bool turn_up = false, turn_down = false, turn_right = false, turn_left = false;

    while (!done)
    {
        currentTime = SDL_GetTicks();
        glm::mat4 ViewMatrix = camera->getViewMatrix();

        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_SetCursor(cursor);
        setCursors(menu_bool, menu_score, menu_play_again, cursor2, x, y);

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
                done = true;

            // MENU MANAGER
            if (menu_bool & !menu_score & !menu_play_again & e.type == SDL_MOUSEBUTTONUP & x > 764 & y > 425 & x < 932 & y < 467)
            {
                menu_bool = false;
            }

            if (menu_play_again & !menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x > 679 & y > 423 & x < 1018 & y < 474)
            {
                menu_play_again = false;
            }

            if (menu_play_again & !menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x > 764 & y > 540 & x < 932 & y < 583)
            {
                menu_play_again = false;
                menu_score = true;
            }

            if (menu_bool & !menu_score & e.type == SDL_MOUSEBUTTONUP & x > 764 & y > 540 & x < 932 & y < 583)
            {
                menu_score = true;
                menu_bool = false;
            }

            if (!menu_bool & menu_score & e.type == SDL_MOUSEBUTTONUP & x > 1447 & y > 789 & x < 1613 & y < 829)
            {
                menu_score = false;
                menu_bool = true;
            }

            if (windowManager.isKeyPressed(SDLK_ESCAPE))
                menu_bool = true;

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

            if (windowManager.isKeyPressed(SDLK_l))    camera->setLocker();

            // PREVENT THE EVENT FROM REPEATING OUTSIDE POLLEVENT
            if (windowManager.isKeyPressed(SDLK_d))    repeat = true;
            if (windowManager.isKeyPressed(SDLK_q))    repeat = true;
            if (windowManager.isKeyPressed(SDLK_z))    repeat = true;
        }

        // MAIN MENU DISPLAY
        if (menu_bool & !menu_score & !menu_play_again)
        {
            menu.setMenuBool(menuShader);
            text.renderMenuText(TextProgram, Characters);
        }

        // SCORE DISPLAY
        if (menu_score & !menu_bool & !menu_play_again)
        {
            menu.setMenuScore(menuShader);
            text.renderScoreText(TextProgram, Characters, scorejson);
        }

        // PLAY AGAIN MENU DISPLAY
        if (menu_play_again & !menu_score & !menu_bool)
        {
            player.setCoord(glm::vec3(2, 3, 0));
            enemy.setCoord(glm::vec3(2, 0, 0));
            enemy.setOrientation(0);
            player.setLife(true);
            player.setOrientation(0);
            camera->rotateLeft(player.getOrientation());
            camera->reset();
            again = true;

            menu.setMenuPlayAgain(menuShader);
            text.renderPlayAgainText(TextProgram, Characters, score);
        }

        // RESET THE GAME DATA IF THE USER WANTS TO PLAY AGAIN
        if (again = true & !menu_play_again & !menu_bool & player.getCoord() == glm::vec3(2, 3, 0))
        {
            courseMap.loadCoins();
            score = 0;
            again = false;
        }

        // GAME DISPLAY
        if (!menu_bool & !menu_score & !menu_play_again)
        {
            // GAME LOOP
            if (player.isLife() & player.getCoord()[1] != courseMap.end() & player.getCoord()[0] >= 0 & player.getCoord()[1] >= 0)
            {
                objet = courseMap.findObject(player.getFloorCoord());
                objet_enemy = courseMap.findObject(enemy.getFloorCoord());

                player.moveManager(objet, camera, score, windowManager, repeat, turn_up, turn_down, turn_right, turn_left, step_turn);
                enemy.moveEnemyManager(objet_enemy);

                if (currentTime - previousTime > speed)
                {
                    player.moveOrientation();
                    enemy.moveOrientation();

                    if (player.isJumping())
                        player.jump(windowManager, repeat, step);

                    if (step >= 10)
                        player.fall(step);

                    if (camera->getCameraType() == 1)
                        camera->moveFront(0.1);

                    if (step_turn < 30 & (turn_right || turn_up || turn_down || turn_left))
                        step_turn += 1;

                    if (step_turn >= 30)
                    {
                        turn_up = false;
                        turn_down = false;
                        turn_left = false;
                        turn_up = false;
                        step_turn = 0;
                    }

                    previousTime = currentTime;
                }
            }

            if (!player.isLife())
            {
                scorejson.addScore(score);
                menu_play_again = true;
            }

            if (player.getFloorCoord().y == courseMap.end())
            {
                scorejson.addScore(score);
                menu_play_again = true;
            }

            camera->eventCamera(windowManager);

            /*********************************
             *      RENDERING CODE           *
             *********************************/

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            

            glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 2000.f / 1000.f, 0.1f, 100.f);
            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));


            // Drawing of the different elements
            light.drawDirectionnal(camera,LightProgram, ProjMatrix, NormalMatrix);
            player.draw(nemo_obj, camera, LightProgram, ProjMatrix);
            enemy.draw(shark_obj, camera, LightProgram, ProjMatrix);
            courseMap.drawMap(cube_path, coin_obj, camera, LightProgram, ProjMatrix, windowManager);
            courseMap.drawObstacle(cube_obstacle, camera, LightProgram, ProjMatrix, windowManager);         
            light.drawPonctual(camera,LightProgram,ProjMatrix,NormalMatrix, player.convertCoord());


            glDepthFunc(GL_LEQUAL);
            SkyboxProgram.use();
            skybox.draw(SkyboxProgram, camera, ProjMatrix, cubemapTexture);

            // Display the text
            text.renderGameText(TextProgram, Characters, score);
        }
        glDisable(GL_BLEND);
        windowManager.swapBuffers();
    }
    courseMap.clearCourseMap();

    return EXIT_SUCCESS;
}