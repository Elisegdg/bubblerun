#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>



//class Player;
namespace rendering{

// Abstract class
class Camera{

protected:
    // Attributs
    unsigned int m_cameraType; // 0 : Trackball / 1 : Eyes
    unsigned int m_locked; //0 : not locked / 1 : locked
    bool m_isRotating;

public:
    
    
    unsigned int getCameraType() const{
        return m_cameraType;
    }


    virtual void moveFront(float delta) = 0;
    virtual void moveLeft(float delta) = 0;
    virtual void rotateLeft(float degrees) = 0;
    virtual void rotateLeftTest(float degrees, int& step)=0;

    virtual void rotateUp(float degrees) = 0;    
    virtual glm::mat4 getViewMatrix() const =0;
    virtual void eventCamera(glimac::SDLWindowManager& windowManager)=0;
    void setLocker(){
        
        if (m_locked == 0)
        {
            m_locked = 1;
        }
        else
        {
            m_locked = 0;
        }
    
    }
};

}

#endif