#ifndef _TRACKBALLCAMERA_HPP
#define _TRACKBALLCAMERA_HPP

#include "glimac/glm.hpp"

namespace rendering {

const float cameraPlayerDistance = 5.f;
const float minDistance = 3.0f;
const float maxDistance = 7.0f;

class TrackballCamera{
private:
    // Attributs
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;


public:
    // Constructor
    TrackballCamera(){
        m_fDistance = cameraPlayerDistance ;
	    m_fAngleX = 0.0;
	    m_fAngleY = 0.0;
    }

    // Destructor
    ~TrackballCamera(){}

    // Methods
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);    
    glm::mat4 getViewMatrix() const;
    float getDistance();

};

}

#endif