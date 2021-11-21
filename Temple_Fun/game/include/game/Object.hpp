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
    void draw() override;
 
};

class Left : public Object
{
public: 
    Left():Object("left"){}
    ~Left()= default;
    void draw() override;

};

class Straight : public Object
{
public:
    Straight():Object("straight"){}
    ~Straight()= default;
    void draw() override;

};


class Obstacle : public Object
{
public:
    Obstacle() : Object("obstacle"){}
    ~Obstacle()= default;
    void draw() override;
};

class  Empty: public Object
{
public:
    Empty() : Object("empty"){}
    ~Empty()= default;
    void draw() override;
};