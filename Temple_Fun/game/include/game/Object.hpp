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



class Object
{
protected:
    glm::vec3 m_coord;
    rendering::Model* m_model;
public:
    Object();
    Object(rendering::Model *model):
        m_model(model){}
    ~Object() = default;
    void addCoord(float x,float y,float z);
    glm::vec3 getCoord();
    virtual void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize);
    
    
};

class Right : public Object
{

public: 
    Right() = default;
    ~Right() = default;
    //void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize) override;
 
};

class Left : public Object
{
public: 
    Left()= default;
    ~Left()= default;
    //void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize) override;

};

class Straight : public Object
{
public:
    Straight()= default;
    ~Straight()= default;
    //void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize);

};


class Obstacle : public Object
{
public:
    Obstacle()= default;
    ~Obstacle()= default;
    void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize);
};

class  Empty: public Object
{
public:
    Empty()= default;
    ~Empty()= default;
    void draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize);
};

#endif