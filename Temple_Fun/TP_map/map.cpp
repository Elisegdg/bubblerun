#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>


using namespace glimac;



int main(int argc, char** argv) {


    CourseMap courseMap;
    courseMap.loadMap("/home/loulou/Documents/synthese_image_imac2/projet/Temple_Fun/assets/test_parcours4.ppm");

    Player player(courseMap);

    Object* objet = courseMap.findObject(player.getCoord()); 

    bool turnRight = false;
    bool turnLeft = false;
    bool doubleturn = false;
 

    while (player.isLife() & player.getCoord()[1] != courseMap.end())
    {
        while ((player.isLife() & player.getCoord()[1] != courseMap.end() & turnRight == false & turnLeft == false & doubleturn ==false) || (player.isLife() & player.getCoord()[1] != courseMap.end() & turnRight == true & turnLeft == true & doubleturn ==false))
        {
            std::cout<<"droit Y1"<<std::endl;
            player.moveY(1);
            objet = courseMap.findObject(player.getCoord());

            std::cout << std::endl;
            objet->draw();
            std::cout << std::endl;
            std::cout << player.getCoord() << std::endl;

            if (objet->getName() == "empty")
            {
                std::cout << "test" << std::endl;
                player.setLife();
            }

            else if (objet->getName() == "right")
            {
                turnRight = true;
                turnLeft = false;
            }
            else if (objet->getName() == "left")
            {
                turnLeft = true;
                turnRight = false;
            }

            else if (objet->getName() == "straight")
            {
                char a = 0;
                std::cout << "q gauche d droite" << std::endl;
                std::cin >> a;
                if (a == 'd')
                {
                    player.moveX(1);
                }
                if (a == 'q')
                {
                    player.moveX(-1);
                }
            }

            else if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }
        }

        while (player.isLife() & player.getCoord()[1] != courseMap.end() & turnRight == true & turnLeft == false & doubleturn ==false)
        {
            std::cout<<"droite X-1"<<std::endl;
            player.moveX(-1);
            objet = courseMap.findObject(player.getCoord());

            std::cout << std::endl;
            objet->draw();
            std::cout << std::endl;
            std::cout << player.getCoord() << std::endl;

            if (objet->getName() == "empty")
            {
                std::cout << "test" << std::endl;
                player.setLife();
            }

            else if (objet->getName() == "right")
            {
                //turnRight = false;
                doubleturn = true;
            }
            else if (objet->getName() == "left")
            {
                turnLeft = true;
            }

            else if (objet->getName() == "straight")
            {
                char a = 0;
                std::cout << "q gauche d droite" << std::endl;
                std::cin >> a;
                if (a == 'd')
                {
                    player.moveY(1);
                }
                if (a == 'q')
                {
                    player.moveY(-1);
                }
            }

            else if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }
        }

        while (player.isLife() & player.getCoord()[1] != courseMap.end() & turnRight == false & turnLeft == true & doubleturn ==false)
        {
            std::cout<<"left X1"<<std::endl;
            player.moveX(1);
            objet = courseMap.findObject(player.getCoord());

            std::cout << std::endl;
            objet->draw();
            std::cout << std::endl;
            std::cout << player.getCoord() << std::endl;

            if (objet->getName() == "empty")
            {
                std::cout << "test" << std::endl;
                player.setLife();
            }

            else if (objet->getName() == "right")
            {
                turnRight = true;
            }
            else if (objet->getName() == "left")
            {
                //turnLeft = false;
                doubleturn = true;
            }

            else if (objet->getName() == "straight")
            {
                char a = 0;
                std::cout << "q gauche d droite" << std::endl;
                std::cin >> a;
                if (a == 'd')
                {
                    player.moveY(1);
                }
                if (a == 'q')
                {
                    player.moveY(-1);
                }
            }

            else if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }
        }

        while (player.isLife() & player.getCoord()[1] != courseMap.end() & doubleturn == true)
        {
            
            std::cout<<"double Y-1"<<std::endl;
            player.moveY(-1);
            objet = courseMap.findObject(player.getCoord());

            std::cout << std::endl;
            objet->draw();
            std::cout << std::endl;
            std::cout << player.getCoord() << std::endl;

            if (objet->getName() == "empty")
            {
                std::cout << "test" << std::endl;
                player.setLife();
            }

            else if (objet->getName() == "right")
            {
                turnRight = true;
                doubleturn = false;
            }
            else if (objet->getName() == "left")
            {
                turnLeft = true;
                doubleturn = false;
            }

            else if (objet->getName() == "straight")
            {
                char a = 0;
                std::cout << "q gauche d droite" << std::endl;
                std::cin >> a;
                if (a == 'd')
                {
                    player.moveX(1);
                }
                if (a == 'q')
                {
                    player.moveX(-1);
                }
            }

            else if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
            {
                player.setLife();
            }
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
