#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
using namespace glimac;

namespace rendering{


// Abstract class
class Camera{

protected:
    // Attributs
    unsigned int m_cameraType; // 0 : Trackball / 1 : Eyes

public:


    //Destructor

    //Methods
    unsigned int getCameraType() const{
        return m_cameraType;
    }


    virtual void moveFront(float delta) = 0;
    virtual void moveLeft(float delta) = 0;
    virtual void rotateLeft(float degrees) = 0;
    virtual void rotateUp(float degrees) = 0;    
    virtual glm::mat4 getViewMatrix() const =0;
    virtual void eventCamera(SDLWindowManager* windowManager)=0;
    virtual void update() = 0;
};



}


#endif