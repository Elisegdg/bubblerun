#include <rendering/EyesCamera.hpp>

#include <math.h>


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
        m_fPhi += glm::radians(degrees);
        computeDirectionVectors();
    }

    void EyesCamera::rotateUp(float degrees){
        m_fTheta += glm::radians(degrees);
        computeDirectionVectors();
    }

    glm::mat4 EyesCamera::getViewMatrix() const{
        glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);        
        return ViewMatrix;
    }




}