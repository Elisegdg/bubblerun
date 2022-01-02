#include <game/Object.hpp>
#include <glimac/glm.hpp>
#include <rendering/Program.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Model.hpp>
#include <rendering/Light.hpp>
#include <glimac/SDLWindowManager.hpp>

namespace game{

void Object::addCoord(float x,float y,float z)
{
    m_coord = glm::vec3(x,y,z);
}

glm::vec3 Object::getCoord()
{
    return m_coord;
}


void Object::draw(rendering::Cube& mesh,const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager)
{
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x-2 , 0, getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.2, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program.uniform1i("uTexture", 0);
    mesh.draw();
    
}

void Obstacle ::draw(rendering::Cube& mesh,const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager)
{

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x-2, 0.4, getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 0.6, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program.uniform1i("uTexture", 0);
    mesh.draw();
}


void Empty::draw(rendering::Cube& mesh,const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager)
{
    return;
}


void Object::drawCoins(rendering::Model& mesh, const rendering::Camera *camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager)
{
    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(getCoord().x-2, 0.2, getCoord().y));
    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(0.08,0.08, 0.08));
    ViewMatrix = glm::rotate(ViewMatrix, windowManager.getTime(), glm::vec3(0,1,0)); // Translation * Rotation
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program.uniform1i("uTexture", 0);
    mesh.draw();
}
}