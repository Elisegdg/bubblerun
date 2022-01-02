/**
 * \file Camera.hpp
 * \brief Declaration of the class Camera
*/


#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>

/*! \namespace rendering
 *  \brief Our rendering library
 *
 *   Namespace regrouping the tools for the rendering engine
 */

namespace rendering{

/*! \class Camera
   * \brief Abstract class of Camera
   *
   *  This class enables to create 2 types of camera that have some similarities
   */
class Camera{

protected:

    unsigned int m_cameraType; /*!< Type of the camera : Trackball is 0 and Eye is 1*/
    unsigned int m_locked; /*!< Camera Locker : 1 is locked, 0 is unlocked*/
    bool m_isRotating; /*!< Boolean that checks if the camera is rotating*/

public:
    /*!
     *  \brief Getter of the type of camera
     *
     *  \return 1 if it is a Trackball camera, 0 if it is an Eye camera
     */
    unsigned int getCameraType() const{
        return m_cameraType;
    }

    /*!
     *  \brief Moves the camera forwards / backwards
     *
     *  \param delta : the step
     * 
     */
    virtual void moveFront(float delta) = 0;

    /*!
     *  \brief Moves the camera to the left/right
     *
     *  \param delta : the step
     * 
     */
    virtual void moveLeft(float delta) = 0;

    /*!
     *  \brief Rotates the camera to the left/right
     *
     *  \param degrees : the rotation angle (in degrees)
     * 
     */
    virtual void rotateLeft(float degrees) = 0;

    /*!
     *  \brief Rotates the camera upwards / downwards
     *
     *  \param degrees : the rotation angle (in degrees)
     * 
     */

    virtual void rotateUp(float degrees) = 0;

    /*!
     *  \brief Calculates and returns the ViewMatrix
     * 
     */    
    virtual glm::mat4 getViewMatrix() const =0;

    /*!
     *  \brief Defines the event related to the camera
     *
     *  \param windowManager : the SDLWindowManager
     * 
     */
    virtual void eventCamera(glimac::SDLWindowManager& windowManager)=0;

    /*!
     *  \brief Switches the camera between locked / unlocked
     * 
     */
    void setLocker(){
        
        if (m_locked == 0)    m_locked = 1;
        else    m_locked = 0;    
    }

    /*!
     *  \brief Reset the camera to its original values
     * 
     */
    virtual void reset()=0;


};

}

#endif