#ifndef _TRACKBALLCAMERA_HPP
#define _TRACKBALLCAMERA_HPP

#include "glimac/glm.hpp"
#include "rendering/Camera.hpp"
#include <glimac/SDLWindowManager.hpp>


namespace rendering {

const float cameraPlayerDistance = 5.f;
const float minDistance = 3.0f;
const float maxDistance = 7.0f;

class TrackballCamera : public Camera{
private:
    // Attributs
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;


public:
    // Constructor
    TrackballCamera(float distance = 5.f, float angleX = 0.f, float angleY = 0.f)
	: m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) 
    {
        m_cameraType = 0;
    }

    // Destructor
    ~TrackballCamera(){}

    // Methods
    void moveFront(float delta);
    void moveLeft(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);    
    glm::mat4 getViewMatrix() const;
    void eventCamera(SDLWindowManager* windowManager);
    float getDistance();
    void update();

};
}

#endif
