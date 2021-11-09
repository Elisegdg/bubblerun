#pragma once
#include "glimac/glm.hpp"


namespace glimac {

class TrackballCamera{
private:
    // Attributs
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    //Constructeur
    TrackballCamera(){
        m_fDistance = 5. ;
	    m_fAngleX = 0.0;
	    m_fAngleY = 0.0;
    }
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    
    glm::mat4 getViewMatrix() const;

};

}