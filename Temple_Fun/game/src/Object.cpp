#include <game/Object.hpp>
#include <glimac/glm.hpp>
#include <rendering/Program.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Model.hpp>


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


void Object::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{

    
 
}

void Right::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{
    //std::cout<<"right"<<std::endl;
     std::cout<<"straight"<<std::endl;
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    std::cout<<"test coord : "<<getCoord().x - 14<<" "<<0.<<" "<<mapSize - getCoord().y<<std::endl;

    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 14, 0,  mapSize-1 - getCoord().y));
    std::cout<<getCoord().x<<" ; "<<0.<<" ; "<<getCoord().y<<std::endl;
    //std::cout<<getCoord().x<<" , "<<getCoord().y<<std::endl;
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);
    //m_model->Model::draw();
}



void Obstacle ::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{
    //std::cout<<"obstacle"<<std::endl;
     std::cout<<"straight"<<std::endl;
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    std::cout<<"test coord : "<<getCoord().x - 14<<" "<<0.<<" "<<mapSize - getCoord().y<<std::endl;

    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 14, 0,  mapSize-1 - getCoord().y));
    std::cout<<getCoord().x<<" ; "<<0.<<" ; "<<getCoord().y<<std::endl;
    //std::cout<<getCoord().x<<" , "<<getCoord().y<<std::endl;
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);
    //m_model->Model::draw();
}

void Straight::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{

    std::cout<<"straight"<<std::endl;
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    std::cout<<"test coord : "<<getCoord().x - 14<<" "<<0.<<" "<<mapSize - getCoord().y<<std::endl;

    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 14, 0,  mapSize-1 - getCoord().y));
    std::cout<<getCoord().x<<" ; "<<0.<<" ; "<<getCoord().y<<std::endl;
    //std::cout<<getCoord().x<<" , "<<getCoord().y<<std::endl;
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);
    //m_model->Model::draw();
    
 
}

void Left::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{
     std::cout<<"straight"<<std::endl;
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    std::cout<<"test coord : "<<getCoord().x - 14<<" "<<0.<<" "<<mapSize - getCoord().y<<std::endl;

    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 14, 0,  mapSize-1 - getCoord().y));
    std::cout<<getCoord().x<<" ; "<<0.<<" ; "<<getCoord().y<<std::endl;
    //std::cout<<getCoord().x<<" , "<<getCoord().y<<std::endl;
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);
    //m_model->Model::draw();
    //std::cout<<"left"<<std::endl;
}


void Empty::draw(rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize)
{
    return;
}