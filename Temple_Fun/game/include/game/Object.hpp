#pragma once 

#include <vector>
#include <iostream>
#include <glimac/glm.hpp>


class Object
{
private:
    glm::vec3 m_coord;
    std::string m_name;
    
public:
    Object(std::string name = 0) :m_coord(glm::vec3(0,0,0)), m_name(name){}
    ~Object() = default;
    void addCoord(float x,float y,float z);
    glm::vec3 getCoord();
    std::string getName();
    virtual void draw();
    
    
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
    Straight():Object("straight"){}
    ~Straight()= default;


};


class Obstacle : public Object
{
public:
    Obstacle() : Object("obstacle"){}
    ~Obstacle()= default;
    void draw();
};

class  Empty: public Object
{
public:
    Empty() : Object("empty"){}
    ~Empty()= default;
    void draw() ;
};