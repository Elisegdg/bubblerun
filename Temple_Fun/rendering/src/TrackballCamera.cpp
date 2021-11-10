#include <rendering/TrackballCamera.hpp>
#include <iostream>
#include <math.h>

namespace rendering {

    void TrackballCamera::moveFront(float delta){
        m_fDistance += delta;
    }

    void TrackballCamera::rotateLeft(float degrees){
        m_fAngleX = degrees / 180 * M_PI;
    }

    void TrackballCamera::rotateUp(float degrees){
        m_fAngleY = degrees / 180 * M_PI;
    }

    glm::mat4 TrackballCamera::getViewMatrix() const{
        glm::mat4 ViewMatrix = glm::mat4(1.0);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, -m_fDistance));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleX, glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, m_fAngleY, glm::vec3(0,1,0));

        return ViewMatrix;

    }

    float TrackballCamera::getDistance(){
        return 3.;
    }




}