#include <rendering/EyesCamera.hpp>
#include <math.h>
#include <glimac/SDLWindowManager.hpp>

namespace rendering {

    void EyesCamera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::vec3(sin(m_fTheta + (M_PI / 2.)), 0., cos(m_fPhi + (M_PI / 2.))) ;
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    void EyesCamera::moveLeft(float t){
        m_Position += t*m_LeftVector;
        computeDirectionVectors();
    }

    void EyesCamera::moveFront(float t){
        m_Position += t*m_FrontVector;
        computeDirectionVectors();
    }


    void EyesCamera::rotateLeft(float degrees){
        const float rad = glm::radians(degrees);
        if(degrees >=0){
            if (m_fPhi + rad < m_fMaxAngleX){
            m_fPhi += rad;
            }
        }
        else{
            if(fabs(m_fPhi + rad) < m_fMaxAngleX){
                m_fPhi += rad;
            }
        }             
       
        computeDirectionVectors();
    }

    void EyesCamera::rotateUp(float degrees){
        const float rad = glm::radians(degrees);
        if(degrees >=0){
            if (m_fTheta + rad < m_fMaxAngleY){
                m_fTheta += rad;
            }
        }
        else{
            if(fabs(m_fTheta + rad) < m_fMaxAngleY){
                m_fTheta += rad;
            }
        }
        
        computeDirectionVectors();
    }

    glm::mat4 EyesCamera::getViewMatrix() const{
        glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);        
        return ViewMatrix;
    }

    void EyesCamera::eventCamera(SDLWindowManager windowManager){
        if(windowManager.isKeyPressed(SDLK_s)) moveFront(-0.1);
        if(windowManager.isKeyPressed(SDLK_z)) moveFront(0.1);
        if(windowManager.isKeyPressed(SDLK_q)) moveLeft(0.1);
        if(windowManager.isKeyPressed(SDLK_d)) moveLeft(-0.1);
        if(windowManager.isKeyPressed(SDLK_i)) rotateLeft(5.0);
        if(windowManager.isKeyPressed(SDLK_k)) rotateUp(5.0);
        
        glm::ivec2 mousePos = glm::ivec2(0.0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            mousePos = windowManager.getMousePosition();
            float mousePosX = mousePos.x/800.0f - 0.5;
            float mousePosY = mousePos.y/600.0f - 0.5;

            rotateLeft(-2*mousePosX);
            rotateUp(-2*mousePosY);

        }
    }




}