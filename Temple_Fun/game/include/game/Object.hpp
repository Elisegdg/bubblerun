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
public:
    Object();
    ~Object() = default;
    void addCoord(float x,float y,float z);
    glm::vec3 getCoord();
    virtual void draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager);
    std::string getName(){
        return m_name;
    }
    
};

class Right : public Object
{

public: 
    Right() {
        m_name = "right";
    }
    ~Right() = default;
 
};

class Left : public Object
{
public: 
    Left(){
    }
    ~Left()= default;

};

class Straight : public Object
{
public:
    Straight(){
    }
    ~Straight()= default;

};


class Obstacle : public Object
{
public:
    Obstacle()= default;
    ~Obstacle()= default;
    void draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager);
};

class  Empty: public Object
{
public:
    Empty()= default;
    ~Empty()= default;
    void draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager);
};

#endif