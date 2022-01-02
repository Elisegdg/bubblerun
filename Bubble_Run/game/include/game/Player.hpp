/**
 * \file Player.hpp
 * \brief Declaration of the class Player
*/


#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <glimac/glm.hpp>
#include "../include/game/CourseMap.hpp"
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>
#include <rendering/Model.hpp>
#include <glimac/SDLWindowManager.hpp>



namespace game{

/*! \class Player
   * \brief Class of Player
   *
   *  This class manages the player and its movements.
   */
class Player
{
private:
    glm::vec3 m_coord; /*!< Coordinates of the Player */
    unsigned int m_coins; /*!< Number of coins gathered */
    bool m_life; /*!< Boolean that says if the player is alive or not */
    float m_orientation; /*!< Orientation of the player regarding the ppm file */
    bool m_isJumping; /*!< Boolean that says if the player is jumping or not */

public:
    
    /*!
     *  \brief Constructor of the Player class
     *
     *  \param Coursemap Map to follow
     *  \param initialPos Initial position of the player.
     */
    Player(CourseMap CourseMap, glm::vec3 initialPos):m_coord(initialPos),m_coins(0),m_life(true),m_orientation(0), m_isJumping(false){}
    
    /*!
     *  \brief Destructor of the Player class
     */
    ~Player() = default;

    /*!
     *  \brief Setter of the Player coordinates
     *
     *  \param coord Coordinates to set
     */
    void setCoord(glm::vec3 coord);

    /*!
     *  \brief Getter of the Player coordinate in the .ppm coordinate system
     */
    glm::vec3 getCoord();

    /*!
     *  \brief Getter of the integral part of the Player coordinate in the .ppm coordinate system
     *
     * Allows to get the cells where the player is
     */
    glm::vec3 getFloorCoord();

    /*!
     *  \brief Converts the Player's coordinates between the .ppm coordinates system and the OpenGl coordinates system
     */
    glm::vec3 convertCoord();

    /*!
     *  \brief Increases the number of Coins of the Player
     */
    void addCoins();

/*!
     *  \brief Getter of the number of Coins that the Player has
     */
    int getCoins();

    /*!
     *  \brief Check if the Player is still alive
     */
    bool isLife();

    /*!
     *  \brief Change the state of life of the Player
     *
     * \param life Boolean to set to the player state of life
     */
    void setLife(bool life);

    /*!
     *  \brief Add a coordinate vector to the current coordinates of the Player 
     *
     *  \param coord_add Coordinate to add
     */    
    void move(glm::vec3 coord_add);

    /*!
     *  \brief Move the Player according to its orientation
     *
     * Enables to determine if moving forwards means incrementing the position on the x or z axis (OpenGl coordinate system)
     */
    void moveOrientation();

    /*!
     *  \brief Setter of the Player's orientation
     *
     *  \param orientation Orientation to set
     */
    void setOrientation(float orientatioin);

    /*!
     *  \brief getter of the Player's orientation
     */
    float getOrientation();

    /*!
     *  \brief Move the player to its right or left
     *
     *  \param windowManager SDLWindowManager to get the event
     *  \param repeat boolean to prevent the event from repeating in SDL1
     *  \param turn_up boolean to determine if the Player will turn in the corner
     *  \param turn_down boolean to determine if the Player will turn in the corner
     *  \param turn_right boolean to determine if the Player will turn in the corner
     *  \param turn_left boolean to determine if the Player will turn in the corner
     */
    void moveside(glimac::SDLWindowManager& windowManager, bool& repeat,bool& turn_up,bool& turn_down,bool& turn_right,bool& turn_left);

    /*!
     *  \brief Makes the player jump
     *
     *  \param windowManager SDLWindowManager to get the event
     *  \param repeat boolean to prevent the event from repeating in SDL1
     *  \param step manage the different step of the jump
     */    
    void jump(glimac::SDLWindowManager& windowManager, bool& repeat, int &step);

    /*!
     *  \brief Makes the player fall after a jump
     *  \param step manage the different step of the fall
     */  
    void fall(int &step);

    /*!
     *  \brief Says if the player is jumping, getter of the jumping boolean
     */  
    bool isJumping();

    /*!
     *  \brief Set the jump
     *
     *  \param windowManager SDLWindowManager to get the event
     *  \param repeat boolean to prevent the event from repeating in SDL1
     */  
    void setJump(glimac::SDLWindowManager &windowManager, bool &repeat);

    /*!
     *  \brief Manages how the Player mooves according to the orientation
     *
     *  \param objet the Object on which the Player is
     *  \param camera the camera to be rotated when there is a turn
     *  \param score The score that increases if the Player collects the coin
     *  \param windowManager the SDLWindowManager to get the event
     *  \param repeat Boolean to prevent the event from repeating in SDL1
     *  \param turn_left boolean to determine if the Player will turn in the corner
     *  \param turn_right boolean to determine if the Player will turn in the corner
     *  \param turn_up boolean to determine if the Player will turn in the corner
     *  \param turn_down boolean to determine if the Player will turn in the corner
     *  \param step_turn manage the different step of the turn
     */  
    void moveManager(Object* objet, rendering::Camera* camera,int &score, glimac::SDLWindowManager& windowManager, bool &repeat, bool& turn_up, bool& turn_down, bool& turn_right, bool& turn_left, int& step_turn);
    
    /*!
     *  \brief Manages how the Enemy mooves according to the orientation
     *
     *  \param objet_enemy the Object on which the Enemy is

     */  
    void moveEnemyManager(Object* objet_enemy);

    /*!
     *  \brief Draw the Player
     *
     *  \param  mesh The corresponding mesh of the Player
     *  \param camera The camera to get the ViewMatrix
     *  \param Program The corresponding shader
     *  \param ProjMatrix The Projection Matrix
     * 
     */
    void draw(rendering::Model& mesh, rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix);

    float getRotation(){
        return glm::radians(m_orientation);
    }
};



}


#endif
