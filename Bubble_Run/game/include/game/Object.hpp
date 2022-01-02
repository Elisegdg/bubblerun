/**
 * \file Object.hpp
 * \brief Declaration of the class Object
*/

#ifndef _OBJECT_HPP
#define _OBJECT_HPP


#include <vector>
#include <iostream>
#include <glimac/glm.hpp>
#include <rendering/Model.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>
#include<rendering/Cube.hpp>
#include<rendering/Texture.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <rendering/Light.hpp>

namespace game{

/*! \class Object
   * \brief Class of Object
   *
   *  This class is the mother class of several types of Objects. 
   *  It manages the different cells of the CourseMap
   */
class Object
{

protected:

    glm::vec3 m_coord; /*!< Coordinate of the object*/
    std::string m_name; /*!< Name of the object (e.g "right") */
    bool m_coins; /*!< Boolean that checks whether ther is a coin on a Object or not */

public:

    /*!
     *  \brief Constructor of the Object class
     *
     *  \param name Name of the object
     *  \param value_coins Boolean related to the presence of a coin.
     */
    Object(std::string name = 0,bool value_coins=0) :m_coord(glm::vec3(0,0,0)), m_name(name),m_coins(value_coins){}    
    
    /*!
     *  \brief Destructor of the Object class
     */
    ~Object() = default;

    /*!
     *  \brief Setter of the coordinate of an object
     *
     *  \param x X component of the coordinate
     *  \param y Y component of the coordinate
     *  \param z Z component of the coordinate
     * 
     */
    void addCoord(float x,float y,float z);

    /*!
     *  \brief Get the coordinates of the Object
     * 
     *  \return the coordinate of the Object
     */
    glm::vec3 getCoord();

    /*!
     *  \brief Draw the object
     *
     *  \param  mesh The corresponding mesh of the object
     *  \param camera The camera to get the ViewMatrix
     *  \param Program The corresponding shader
     *  \param ProjMatrix The Projection Matrix
     *  \param windowManager The SDLWindowManager
     * 
     */
    virtual void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
    
    /*!
     *  \brief Draw the coin
     *
     *    Checks all the object to determine if there is a coin or not. 
     *    If it's the case, it draws the coin
     *
     *  \param  mesh The corresponding mesh of the object
     *  \param camera The camera to get the ViewMatrix
     *  \param Program The corresponding shader
     *  \param ProjMatrix The Projection Matrix
     *  \param windowManager The SDLWindowManager
     * 
     */
    void drawCoins(rendering::Model& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
    
    /*!
     *  \brief Setter of the Coin
     *
     *  Set the coin boolean
     *  \param  coins Coin boolean to set
     * 
     */
    void setCoins(bool coins){m_coins = coins;}

    /*!
     *  \brief Getter of the type of object
     * 
     */
    std::string getName()const {
        return m_name;
    }

    /*!
     *  \brief Getter of the coin boolean
     * 
     */

    bool getIfCoins() const {
        return m_coins;
        
    }

    /*!
     *  \brief Coin Remover
     *
     *  Set the coin boolean to false 
     */
    void removeCoin(){
        m_coins = 0;
    }
    
    
};

/*! \class Right
   * \brief Class of Right
   *
   *  This class is the children class of Object.
   *  It indicates a right corner
   */
class Right : public Object
{

public: 
    /*!
     *  \brief Constructor of the Right class
     *
     * It calls the Object constructor and sets the name to "right"
     */
    Right():Object("right"){}

    /*!
     *  \brief Destructor of the Right class
     */
    ~Right() = default;
 
};

/*! \class Left
   * \brief Class of Left
   *
   *  This class is the children class of Object.
   *  It indicates a left corner
   */
class Left : public Object
{
public: 
    /*!
     *  \brief Constructor of the Left class
     *
     * It calls the Object constructor and sets the name to "left"
     */
    Left():Object("left"){}

    /*!
     *  \brief Destructor of the Left class
     */
    ~Left()= default;

};

/*! \class Up
   * \brief Class of Up
   *
   *  This class is the children class of Object.
   *  It indicates that the direction of the path on the ppm is upwards
   */
class Up : public Object
{
public: 

    /*!
     *  \brief Constructor of the Up class
     *
     * It calls the Object constructor and sets the name to "up"
     */
    Up():Object("up"){}

    /*!
     *  \brief Destructor of the Up class
     */
    ~Up()= default;

};

/*! \class Down
   * \brief Class of Down
   *
   *  This class is the children class of Object.
   *  It indicates that the direction of the path on the ppm is downwards
   */
class Down : public Object
{
public: 
    /*!
     *  \brief Constructor of the Down class
     *
     * It calls the Object constructor and sets the name to "down"
     */
    Down():Object("down"){}

    /*!
     *  \brief Destructor of the Down class
     */
    ~Down()= default;

};

/*! \class Straight
   * \brief Class of Straight
   *
   *  This class is the children class of Object.
   *  It indicates that it is a "regular" cell of path. 
   *  It can contain coins.
   */
class Straight : public Object
{

public:
    /*!
     *  \brief Constructor of the Straight class
     *
     * It calls the Object constructor and sets the name to "straight"
     * 
     *  \param value Coin boolean
     */
    Straight(bool value):Object("straight",value){}

    /*!
     *  \brief Destructor of the Straight class
     */
    ~Straight()= default;

};

/*! \class Obstacle
   * \brief Class of Obstacle
   *
   *  This class is the children class of Object.
   *  It indicates that it is an obstacle
   */
class Obstacle : public Object
{
public:

    /*!
     *  \brief Constructor of the Obstacle class
     *
     * It calls the Object constructor and sets the name to "obstacle"
     */
    Obstacle() : Object("obstacle"){}

    /*!
     *  \brief Destructor of the Object class
     */
    ~Obstacle()= default;
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};

/*! \class Empty
   * \brief Class of Empty
   *
   *  This class is the children class of Object.
   *  It indicates that there is no cell of path to draw.
   *  It can contain coins.
   */
class  Empty: public Object
{
public:
    /*!
     *  \brief Constructor of the Empty class
     *
     * It calls the Object constructor and sets the name to "empty"
     */
    Empty() : Object("empty"){}

    /*!
     *  \brief Destructor of the Empty class
     */
    ~Empty()= default;
    
    /*!
     *  \brief Draw the empty
     *
     *  Specifies to NOT draw anythin
     * 
     *  \param mesh The mesh corresponding to the obstacle
     *  \param camera The camera (to get the ViewMatrix)
     *  \param Program The shader
     *  \param ProjMatrix The Projection Matrix
     *  \param WindowManager The SDLWindowManager
     */
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};

/*! \class Coins
   * \brief Class of Coins
   *
   *  This class is the children class of Object.
   *  It indicates that it is a coin 
   */
class Coins: public Object
{
    public:

    /*!
     *  \brief Draw the coins
     *
     *  \param mesh The mesh corresponding to the coin
     *  \param camera The camera (to get the ViewMatrix)
     *  \param Program The shader
     *  \param ProjMatrix The Projection Matrix
     *  \param WindowManager The SDLWindowManager
     */
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};

}
#endif
