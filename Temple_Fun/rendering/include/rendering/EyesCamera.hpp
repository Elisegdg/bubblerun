#ifndef _EYESCAMERA_HPP
#define _EYESCAMERA_HPP

#include "glimac/glm.hpp"
#include "rendering/Camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <game/Player.hpp>



namespace rendering {
class EyesCamera : public Camera{
private:
    // Attributs
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    float m_fMaxAngleX;
    float m_fMaxAngleY;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
    Player* m_player;
    

public:
    // Constructor
    EyesCamera(Player* player){
        m_player = player;
        m_Position = glm::vec3(0, 2., 0); //2is the "height" of the hero, we need to define it somewhere
	    m_fPhi = 0.;
        m_fTheta = 0.;
        m_cameraType = 1;
        m_fMaxAngleX = 0.6;
        m_fMaxAngleY = 0.8;
        m_locked = 0;
	    computeDirectionVectors();
    }

    //Destructor
    ~EyesCamera(){}

    // Methods
    void moveLeft(const float t);
    void moveFront(const float t);
    void rotateLeft(const float degrees);
    void rotateUp(const float degrees);
    glm::mat4 getViewMatrix() const;
    void rotateLeftMouse(const float degrees);
    void eventCamera(SDLWindowManager& windowManager);
    
    
    
    void computeDirectionVectors();

    float getTheta(){
        return m_fTheta;
    }
    



};

}


#endif