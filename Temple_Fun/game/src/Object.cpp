#include "../include/game/Object.hpp"
#include <glimac/glm.hpp>
#include <rendering/Cube.hpp>

Object::Object(): m_coord(glm::vec3(0,0,0))
{

}


void Object::addCoord(float x,float y,float z)
{
    m_coord = glm::vec3(x,y,z);
}

glm::vec3 Object::getCoord()
{
    return m_coord;
}




void Right::draw(glm::mat4 ViewMatrix, int mapSize)
{
    std::cout<<"right"<<std::endl;
}

void Object::draw(glm::mat4 ViewMatrix, int mapSize)
{
    std::cout<<"test"<<std::endl;
}



void Obstacle ::draw(glm::mat4 ViewMatrix, int mapSize)
{
    std::cout<<"obstacle"<<std::endl;
}

void Straight::draw(glm::mat4 ViewMatrix, int mapSize)
{
    //std::cout<<"straight"<<std::endl;
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 14 , 0., 19 - getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    

}

void Left::draw(glm::mat4 ViewMatrix, int mapSize)
{
    std::cout<<"left"<<std::endl;
}


void Empty::draw(glm::mat4 ViewMatrix, int mapSize){
    return;
}