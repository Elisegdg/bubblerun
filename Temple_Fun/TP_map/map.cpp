#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>


using namespace glimac;



int main(int argc, char** argv) {


    CourseMap courseMap;
    courseMap.loadMap("/home/clara/Documents/Projet/Temple_Fun/assets/test_parcours4.ppm");

    Player player(courseMap);

    Object* objet = courseMap.findObject(player.getCoord()); 

    bool right = false;
    bool left = false;
    bool up = false;
    bool down = true;
 

    while (player.isLife() & player.getCoord()[1] != courseMap.end())
    {

        objet = courseMap.findObject(player.getCoord());

        std::cout<<std::endl;
        std::cout<<std::endl;

        

        
        std::cout << player.getCoord() << std::endl;

        if (objet->getName() == "straight")
        {
            char a = 0;
            std::cout << "q gauche d droite" << std::endl;
            std::cin >> a;

            if (right == true)
            {
                if (a == 'd')
                {
                    player.move(glm::vec3(0,1,0));
                }
                if (a == 'q')
                {
                    player.move(glm::vec3(0,-1,0));
                }
            }

            if (left == true)
            {
                if (a == 'd')
                {
                    player.move(glm::vec3(0,-1,0));
                }
                if (a == 'q')
                {
                    player.move(glm::vec3(0,1,0));
                }
            }

            if (up == true)
            {
                if (a == 'd')
                {
                    player.move(glm::vec3(-1,0,0));
                }
                if (a == 'q')
                {
                    player.move(glm::vec3(1,0,0));
                }
            }

            if (down == true)
            {
                if (a == 'd')
                {
                    player.move(glm::vec3(1,0,0));
                }
                if (a == 'q')
                {
                    player.move(glm::vec3(-1,0,0));
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
        
        if (right ==true)
        {
            player.move(glm::vec3(1,0,0));
        }

        if (left == true)
        {
            player.move(glm::vec3(-1,0,0));
        }

        if (up==true)
        {
            player.move(glm::vec3(0,-1,0));
        }

        if (down==true)  
        {
            player.move(glm::vec3(0,1,0));
        }


        

    }

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }
 

    return EXIT_SUCCESS;
}
