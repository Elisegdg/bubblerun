#include <rendering/TrackballCamera.hpp>
#include <math.h>
#include <glimac/SDLWindowManager.hpp>


namespace rendering {

    void TrackballCamera::moveFront(float delta){
        m_fDistance += delta;
    }

    void TrackballCamera::moveLeft(float delta){
        return;
    }
    void TrackballCamera::rotateLeft(float degrees){
        m_fAngleX = glm::radians(degrees);
    }

    void TrackballCamera::rotateUp(float degrees){
        m_fAngleY = glm::radians(degrees);
    }

    glm::mat4 TrackballCamera::getViewMatrix() const{
        glm::mat4 ViewMatrix = glm::mat4(1.0);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0., 0., -m_fDistance));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0,1,0));
        ViewMatrix = glm::translate(ViewMatrix, -m_player->convertCoord());
        

        return ViewMatrix;

    }

    float TrackballCamera::getDistance(){
        return m_fDistance;
    }

    void TrackballCamera::eventCamera(SDLWindowManager* windowManager){
        glm::ivec2 mousePos = windowManager->getMousePosition();
        /*if(windowManager->isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
            std::cout<<mousePos<<std::endl;
            moveFront(0.03);
        }
        else if(windowManager->isMouseButtonPressed(SDL_BUTTON_LEFT)) moveFront(-0.03);*/
        if (windowManager->isMouseButtonPressed(SDL_BUTTON_LEFT))
        {
            rotateLeft( mousePos.y/2);
            rotateUp( mousePos.x/2);
            std::cout<<"mousePos y :  "<<mousePos.y<<std::endl;
            std::cout<<"mousePos x  :  "<<mousePos.x<<std::endl;
        }
    }
    



}