#include "../include/game/Object.hpp"
#include <glimac/glm.hpp>


void Object::addCoord(float x,float y,float z)
{
    m_coord = glm::vec3(x,y,z);
}

glm::vec3 Object::getCoord()
{
    return m_coord;
}

std::string Object::getName()
{
    return m_name;
}




void Object::draw()
{
    std::cout<<"test"<<std::endl;
}

void Empty::draw()
{
    std::cout<<"empty"<<std::endl;
}

void Obstacle ::draw()
{
    std::cout<<"obstacle"<<std::endl;
}

