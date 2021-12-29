#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>
#include <include/ft2build.h>
#include FT_FREETYPE_H  

using namespace glimac;



int main(int argc, char** argv) {

    // //freetype 
    // //load arial 
                  

    // CourseMap courseMap;
    // courseMap.loadMap("../Temple_Fun/assets/test_parcours4.ppm");


    // Player player(courseMap);

    // Object* objet = courseMap.findObject(player.getCoord()); 

    
 

    // while (player.isLife() & player.getCoord()[1] != courseMap.end() & player.getCoord()[0]>=0 & player.getCoord()[1]>=0 )
    // {

    //     objet = courseMap.findObject(player.getCoord());

    //     std::cout<<std::endl;
    //     std::cout<<objet->getIfCoins();
    //     std::cout<<std::endl;

        

        
    //     std::cout << player.getCoord() << std::endl;

    //     if (objet->getName() == "straight")
    //     {
            
    //         char a = 0;
    //         std::cout << "q gauche d droite" << std::endl;
    //         std::cin >> a;
    //         player.moveside(a);
            
    //     }
    //     if (objet->getName() == "up")
    //     {
            
    //         player.setOrientation(180.);
 

    //     }
    //     if (objet->getName() == "down")
    //     {
            
    //         player.setOrientation(0.);
    //     }
        
    //     if (objet->getName() == "right")
    //     {
        
    //         player.setOrientation(90.);
    //     }
    //     if (objet->getName() == "left")
    //     {
           
    //         player.setOrientation(-90.);
    //     }
    //     if (objet->getName() == "empty")
    //     {

    //         player.setLife();
            
    //     }

    //     if (objet->getName() == "obstacle" & player.getCoord()[2] == 0)
    //     {
    //         player.setLife();
    //     }
        
       

    //     player.moveOrientation();


        

    // }

    // // Initialize SDL and open a window
    // SDLWindowManager windowManager(800, 600, "GLImac");

    // // Initialize glew for OpenGL3+ support
    // GLenum glewInitError = glewInit();
    // if(GLEW_OK != glewInitError) {
    //     std::cerr << glewGetErrorString(glewInitError) << std::endl;
    //     return EXIT_FAILURE;
    // }

    // std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    // std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // /*********************************
    //  * HERE SHOULD COME THE INITIALIZATION CODE
    //  *********************************/

    // // Application loop:
    // bool done = false;
    // while(!done) {
    //     // Event loop:
    //     SDL_Event e;
    //     while(windowManager.pollEvent(e)) {
    //         if(e.type == SDL_QUIT) {
    //             done = true; // Leave the loop after this iteration
    //         }
    //     }

    //     /*********************************
    //      * HERE SHOULD COME THE RENDERING CODE
    //      *********************************/

    //     // Update the display
    //     windowManager.swapBuffers();
    // }
 

    // return EXIT_SUCCESS;
}
