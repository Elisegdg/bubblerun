#pragma once 

#include <vector>
#include <iostream>
#include <glimac/glm.hpp>


class Object
{
private:
    glm::vec3 m_coord;
public:
    Object();
    ~Object() = default;
    void AddCoord(float x,float y,float z);
    glm::vec3 GetCoord();
    virtual void Draw();
    
    
};

class Right : public Object
{

public: 
    Right() = default;
    ~Right() = default;
    void Draw() override;
 
};

class Left : public Object
{
public: 
    Left()= default;
    ~Left()= default;
    void Draw() override;

};

class Straight : public Object
{
public:
    Straight()= default;
    ~Straight()= default;
    void Draw() override;

};


class Obstacle : public Object
{
public:
    Obstacle()= default;
    ~Obstacle()= default;
    void Draw() override;
};

class  Empty: public Object
{
public:
    Empty()= default;
    ~Empty()= default;
    void Draw() override;
};