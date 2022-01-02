#include <rendering/TrackballCamera.hpp>
#include <math.h>
#include <glimac/SDLWindowManager.hpp>

namespace rendering
{

    void TrackballCamera::moveFront(float delta)
    {
        m_fDistance += delta;
    }

    void TrackballCamera::moveLeft(float delta)
    {
        return;
    }
    void TrackballCamera::rotateLeft(float degrees)
    {
        if(degrees==0){
            m_fAngleY = glm::radians(180.);
        }
        else if(degrees==180){
            m_fAngleY = glm::radians(0.);
        }
        else m_fAngleY = glm::radians(degrees);
    }


    void TrackballCamera::rotateUp(float degrees)
    {
        m_fAngleX = glm::radians(degrees);
    }

    glm::mat4 TrackballCamera::getViewMatrix() const
    {
        glm::mat4 ViewMatrix = glm::mat4(1.0);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0., 0., -m_fDistance));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0, 1, 0));
        ViewMatrix = glm::translate(ViewMatrix, -m_player->convertCoord());

        return ViewMatrix;
    }


    void TrackballCamera::eventCamera(glimac::SDLWindowManager& windowManager)
    {
        glm::ivec2 mousePos = windowManager.getMousePosition();

        if (!m_locked)
        {
            if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT))
                moveFront(0.03);
            else if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
                moveFront(-0.03);

            if (windowManager.isKeyPressed(SDLK_LCTRL))
            {

                rotateLeft(mousePos.x / 5);
                rotateUp(mousePos.y / 5);
            }
            
        }
    }

    void TrackballCamera::reset()
    {
        m_fDistance = 5.f;
        m_fAngleX = 0.7f; 
        m_fAngleY = 600.f;
    }

}
