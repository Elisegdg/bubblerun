#include <rendering/EyesCamera.hpp>
#include <math.h>
#include <glimac/SDLWindowManager.hpp>

namespace rendering
{

    void EyesCamera::computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::cross(glm::vec3(0, 1, 0), m_FrontVector);
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    void EyesCamera::moveLeft(float t)
    {
        m_Position = glm::vec3(m_player->convertCoord().x, m_player->convertCoord().y +2. , m_player->convertCoord().z);
        computeDirectionVectors();
    }

    void EyesCamera::moveFront(float t)
    {

        m_Position = glm::vec3(m_player->convertCoord().x, m_player->convertCoord().y +2., m_player->convertCoord().z);
        computeDirectionVectors();
    }

    void EyesCamera::rotateLeft(float degrees)
    {
        const float rad = glm::radians(degrees);
        m_fPhi = rad;
        computeDirectionVectors();
    }

    void EyesCamera::rotateLeftMouse(float degrees)
    {
        const float rad = glm::radians(degrees);
        if (!m_locked)
        {

            if (m_fPhi + rad <= glm::radians(m_player->getOrientation()) + m_fMaxAngleX && m_fPhi + rad >= glm::radians(m_player->getOrientation()) - m_fMaxAngleX)
            {
                m_fPhi += rad;
            }
        }
        computeDirectionVectors();
    }

    void EyesCamera::rotateUp(float degrees)
    {
        const float rad = glm::radians(degrees);
        if (!m_locked)
        {
            if (degrees >= 0)
            {
                if (m_fTheta + rad < m_fMaxAngleY)
                {
                    m_fTheta += rad;
                }
            }
            else
            {
                if (fabs(m_fTheta + rad) < m_fMaxAngleY)
                {
                    m_fTheta += rad;
                }
            }
        }

        computeDirectionVectors();
    }

    glm::mat4 EyesCamera::getViewMatrix() const
    {
        glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
        return ViewMatrix;
    }


    void EyesCamera::eventCamera(glimac::SDLWindowManager& windowManager)
    {
        
        if (windowManager.isKeyPressed(SDLK_q))
            moveLeft(1);
        if (windowManager.isKeyPressed(SDLK_d))
            moveLeft(-1);
        
        
        glm::ivec2 mousePos = glm::ivec2(0.0);
        if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
        {
            mousePos = windowManager.getMousePosition();
            float mousePosX = mousePos.x / 1700.0f - 0.5;
            float mousePosY = mousePos.y / 900.0f - 0.5;

            rotateLeftMouse(-2 * mousePosX);
            rotateUp(-2 * mousePosY);
        }
    }

    void EyesCamera::reset()
    {
        m_fPhi = 0.;
        m_fTheta = -0.4;
    }

}