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
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, -m_fDistance));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0,1,0));

        return ViewMatrix;

    }

    float TrackballCamera::getDistance(){
        return m_fDistance;
    }

    void TrackballCamera::eventCamera(SDLWindowManager* windowManager){
        glm::ivec2 mousePos = windowManager->getMousePosition();
        if(windowManager->isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
            moveFront(0.03);
        }
        else if(windowManager->isMouseButtonPressed(SDL_BUTTON_LEFT)) moveFront(-0.03);

        rotateLeft( mousePos.y );
        rotateUp( mousePos.x );
    }
    void TrackballCamera::update(){
        return;
    }



}