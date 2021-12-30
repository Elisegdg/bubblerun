
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



class Object
{

protected:
    glm::vec3 m_coord;
    std::string m_name;
    bool m_coins;
public:
    Object(std::string name = 0,bool value_coins=0) :m_coord(glm::vec3(0,0,0)), m_name(name),m_coins(value_coins){}    
    ~Object() = default;
    void addCoord(float x,float y,float z);
    glm::vec3 getCoord();
    virtual void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
    void drawCoins(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
    void setCoins(bool coins){m_coins = coins;}

    std::string getName(){
        return m_name;
    }
    bool getIfCoins(){
        return m_coins;
        
    }
    void removeCoin(){
        m_coins = 0;
    }

    
};

class Right : public Object
{

public: 
    Right():Object("right"){}
    ~Right() = default;
 
};

class Left : public Object
{
public: 
    Left():Object("left"){}
    ~Left()= default;

};

class Up : public Object
{
public: 
    Up():Object("up"){}
    ~Up()= default;

};

class Down : public Object
{
public: 
    Down():Object("down"){}
    ~Down()= default;

};
class Straight : public Object
{

public:
    Straight(bool value):Object("straight",value){}
    ~Straight()= default;
    



};


class Obstacle : public Object
{
public:
    Obstacle() : Object("obstacle"){}
    ~Obstacle()= default;
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};

class  Empty: public Object
{
public:
    Empty() : Object("empty"){}
    ~Empty()= default;
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};

class Coins: public Object
{
    public:
    void draw(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager);
};


#endif
