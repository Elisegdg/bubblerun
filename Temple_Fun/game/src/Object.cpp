#include <game/Object.hpp>
#include <glimac/glm.hpp>
#include <rendering/Program.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Model.hpp>
#include <glimac/SDLWindowManager.hpp>



void Object::addCoord(float x,float y,float z)
{
    m_coord = glm::vec3(x,y,z);
}

glm::vec3 Object::getCoord()
{
    return m_coord;
}


void Object::draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager)
{
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 1, 0,  getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0,-3*windowManager->getTime()));

    //camera->rotateLeft(45.);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);

    
}

void Obstacle ::draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager)
{

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x - 1, 0.4,  getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 1, 1));
    //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0,-3*windowManager->getTime()));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);
}


void Empty::draw(const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, int mapSize, glimac::SDLWindowManager* windowManager)
{
    return;
}
