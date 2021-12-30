#ifndef _TRACKBALLCAMERA_HPP
#define _TRACKBALLCAMERA_HPP

#include "glimac/glm.hpp"
#include "rendering/Camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <game/Player.hpp>


namespace rendering {

const float cameraPlayerDistance = 2.f;
const float minDistance = 3.0f;
const float maxDistance = 7.0f;

class TrackballCamera : public Camera{
private:
    // Attributs
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
    Player* m_player;

public:
    // Constructor
    TrackballCamera(Player* player, float distance = 5.f, float angleX = 0.7f, float angleY = 600.f)
	:m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) 
    {
        m_cameraType = 0;
        m_player = player;
        m_locked = 0;
        m_isRotating = false;
    }

    // Destructor
    ~TrackballCamera(){}

    // Methods
    void moveFront(const float delta);
    void moveLeft(const float delta);
    void rotateLeft(const float degrees);
    void rotateUp(const float degrees);    
    glm::mat4 getViewMatrix() const;
    void eventCamera(SDLWindowManager& windowManager);
    float getDistance();
    
};

}

#endif
