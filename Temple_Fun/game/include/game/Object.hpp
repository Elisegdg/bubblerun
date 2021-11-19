#pragma once 

#include <vector>
#include <iostream>
#include <glimac/glm.hpp>
#include<rendering/Model.hpp>




class Object
{
private:
    glm::vec3 m_coord;
    Model* m_model;
public:
    Object();
    Object(Model *model):
        m_model(model){}
    ~Object() = default;
    void addCoord(float x,float y,float z);
    glm::vec3 getCoord();
    virtual void draw(glm::mat4 ViewMatrix, int mapSize);
    
    
};

class Right : public Object
{

public: 
    Right() = default;
    ~Right() = default;
    void draw(glm::mat4 ViewMatrix, int mapSize) override;
 
};

class Left : public Object
{
public: 
    Left()= default;
    ~Left()= default;
    void draw(glm::mat4 ViewMatrix, int mapSize) override;

};

class Straight : public Object
{
public:
    Straight()= default;
    ~Straight()= default;
    void draw(glm::mat4 ViewMatrix, int mapSize) ;

};


class Obstacle : public Object
{
public:
    Obstacle()= default;
    ~Obstacle()= default;
    void draw(glm::mat4 ViewMatrix, int mapSize) override;
};

class  Empty: public Object
{
public:
    Empty()= default;
    ~Empty()= default;
    void draw(glm::mat4 ViewMatrix, int mapSizeSize) override;
};