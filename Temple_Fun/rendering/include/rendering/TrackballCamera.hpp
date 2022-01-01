/**
 * \file TrackballCamera.hpp
 * \brief Declaration of the class TrackballCamera
*/

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


/*! \class TrackballCamera
   * \brief Player-centric Camera
   *
   *  This class creates a camera where the player is constantly at the center of the view.
   */
class TrackballCamera : public Camera{

private:

    float m_fDistance;/*!< Distance camera-player */
    float m_fAngleX;/*!< Rotation angle along the X axis*/
    float m_fAngleY; /*!< Rotation angle along the Y axis*/
    game::Player* m_player;/*!< Player to follow */

public:
    
    /*!
     *  \brief Constructor of the Trackball class
     *
     * Sets the cameraType at 0
     * 
     *  \param player : The player that is centered on the view
     *  \param distance : The distance between the camera and the player
     *  \param angleX : The initial rotation angle on the X axis
     *  \param distance : The initial rotation angle on the Y axis 
     * 
     */
    TrackballCamera(game::Player* player, float distance = 5.f, float angleX = 0.7f, float angleY = 600.f)
	:m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) 
    {
        m_cameraType = 0;
        m_player = player;
        m_locked = 0;
        m_isRotating = false;
    }

    /*!
     *  \brief Destructor of the EyeCamera class
     */
    ~TrackballCamera(){}

    void moveFront(float delta);
    void moveLeft(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);    
    glm::mat4 getViewMatrix() const;
    void eventCamera(glimac::SDLWindowManager& windowManager);
    void reset();
    

};
}

#endif
