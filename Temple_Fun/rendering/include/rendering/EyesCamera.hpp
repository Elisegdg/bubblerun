#ifndef _EYESCAMERA_HPP
#define _EYESCAMERA_HPP

#include "glimac/glm.hpp"


#pragma once
#include "glimac/glm.hpp"
#include <math.h>


namespace rendering {

class EyesCamera{
private:
    // Attributs
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    

public:
    // Constructor
    EyesCamera(){
        m_Position = glm::vec3(0.,0.,0.);
	    m_fPhi = M_PI;
        m_fTheta = 0.;
	    computeDirectionVectors();
    }

    // Methods
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    
    void computeDirectionVectors();
    
    glm::mat4 getViewMatrix() const;

};

}


#endif