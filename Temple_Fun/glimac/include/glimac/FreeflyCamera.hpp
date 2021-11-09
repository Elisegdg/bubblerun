#pragma once
#include "glimac/glm.hpp"
#include <math.h>


namespace glimac {

class FreeflyCamera{
private:
    // Attributs
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    //Méthodes
    void computeDirectionVectors();

public:
    //Constructeur
    FreeflyCamera(){
        m_Position = glm::vec3(0.,0.,0.);
	    m_fPhi = M_PI;
        m_fTheta = 0.;
	    computeDirectionVectors();
    }
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    
    glm::mat4 getViewMatrix() const;

};

}