#include "../include/map/object.hpp"
#include <glimac/glm.hpp>

Object::Object(): m_coord(glm::vec3(0,0,0))
{
}


void Object::AddCoord(float x,float y,float z)
{
    m_coord = glm::vec3(x,y,z);
}

glm::vec3 Object::GetCoord()
{
    return m_coord;
}


void Right::Draw()
{
    std::cout<<"right"<<std::endl;
}

void Object::Draw()
{
    std::cout<<"test"<<std::endl;
}

void Empty::Draw()
{
    std::cout<<"empty"<<std::endl;
}

void Obstacle ::Draw()
{
    std::cout<<"obstacle"<<std::endl;
}

void Straight::Draw()
{
    std::cout<<"straight"<<std::endl;
}

void Left::Draw()
{
    std::cout<<"left"<<std::endl;
}