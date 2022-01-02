/**
 * \file EyesCamera.hpp
 * \brief Declaration of the class EyesCamera
*/

#ifndef _EYESCAMERA_HPP
#define _EYESCAMERA_HPP

#include "glimac/glm.hpp"
#include "rendering/Camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <game/Player.hpp>



namespace rendering {

/*! \class EyesCamera
   * \brief First Person Camera
   *
   *  This camera is attached to the Player and shows what the Player sees
   */
class EyesCamera : public Camera{

private:
    glm::vec3 m_Position; /*!< Position of the camera in a Vector of 3 dimensions*/
    float m_fPhi; /*!< Spheric coordinate Phi */
    float m_fTheta; /*!< Spheric coordinate Theta*/
    float m_fMaxAngleX; /*!< The maximum rotation angle of the camera (left-right)*/
    float m_fMaxAngleY; /*!< The maximum rotation angle of the camera (up-down)*/
    glm::vec3 m_FrontVector; /*!< Front Vector */
    glm::vec3 m_LeftVector; /*!< Left Vector */
    glm::vec3 m_UpVector; /*!< Up Vector */
    game::Player* m_player; /*!< The player on which the camera is attached */
    

public:
    
    /*!
     *  \brief Constructor of the EyeCamera class
     *
     * Sets the cameraType at 1
     *
     *  \param player : the player on which the camera is attached
     */
    EyesCamera(game::Player* player){
        m_player = player;
        m_Position = glm::vec3(0, 2., 0); //2is the "height" of the hero
	    m_fPhi = 0.;
        m_fTheta = -0.4;
        m_cameraType = 1;
        m_fMaxAngleX = 0.6;
        m_fMaxAngleY = 0.8;
        m_locked = 0;
	    computeDirectionVectors();
    }

    /*!
     *  \brief Destructor of the EyeCamera class
     */
    ~EyesCamera(){}

    
    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;

    /*!
     *  \brief Rotates the camera to the left/right and blocks it at a certain angle
     *
     *  \param degrees : the rotation angle (in degrees)
     * 
     */
    void rotateLeftMouse(float degrees);
    void eventCamera(glimac::SDLWindowManager& windowManager);

    /*!
     *  \brief Calculates the Up / Left / Front vectors 
     */
    void computeDirectionVectors();
    void reset();


};

}


#endif