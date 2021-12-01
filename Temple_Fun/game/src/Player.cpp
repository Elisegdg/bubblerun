
#include "../include/game/Player.hpp"
#include "../include/game/CourseMap.hpp"
#include <glimac/glm.hpp>



void Player::setCoord(glm::vec3 coord)
{
    m_coord = coord;
}


glm::vec3 Player::getCoord()
{
    return m_coord;
}

void Player::addCoins()
{
    m_coins ++;
}

int Player::getCoins()
{
    return m_coins;
}

bool Player::isLife()
{
    return m_life;
}


void Player::move(glm::vec3 coord_move)
{
    m_coord = glm::vec3(m_coord[0]+coord_move[0],m_coord[1]+coord_move[1],m_coord[2]+coord_move[2]);
}

void Player::setLife()
{
    m_life =false;
}

glm::vec3 Player::convertCoord(){
    return glm::vec3(getCoord().x - 1, 0, getCoord().y);
}

void Player::draw(rendering::Model* mesh, rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix)
{

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, convertCoord());
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0.6,0));

    ViewMatrix = glm::scale(ViewMatrix,glm::vec3(1, 1, 1));
    //ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0,0,-3*windowManager->getTime()));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program->uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program->uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program->uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program->uniform1i("uTexture", 0);

    mesh->draw();

}


void Player::moveOrientation()
{
    if (m_orientation == 0.)
    {
        move(glm::vec3(0,1,0));
    }
    if (m_orientation == 90.)
    {
        move(glm::vec3(1,0,0));
    }
    if (m_orientation == -90.)
    {
        move(glm::vec3(-1,0,0));
    }
    if (m_orientation == 180.)
    {
        move(glm::vec3(0,-1,0));
    }
    
    
}

void Player::setOrientation(float orientation )
{
    m_orientation = orientation;
}

float Player::getOrientation()
{
    return m_orientation;
}

void Player::moveside(glimac::SDLWindowManager* windowManager)
{
    if (m_orientation == 0.)
    {
        if (windowManager->isKeyPressed(SDLK_d))
        {
            move(glm::vec3(-1, 0, 0));
        }
        if (windowManager->isKeyPressed(SDLK_q))
        {
            move(glm::vec3(1, 0, 0));
        }
    }
    if (m_orientation == 90.)
    {
        if (windowManager->isKeyPressed(SDLK_d))
        {
            move(glm::vec3(0, 1, 0));
        }
        if (windowManager->isKeyPressed(SDLK_q))
        {
            move(glm::vec3(0, -1, 0));
        }
    }
    if (m_orientation == -90.)
    {
        if (windowManager->isKeyPressed(SDLK_d))
        {
            move(glm::vec3(0, -1, 0));
        }
        if (windowManager->isKeyPressed(SDLK_q))
        {
            move(glm::vec3(0, 1, 0));
        }
    }
    if (m_orientation == 180.)
    {
        if (windowManager->isKeyPressed(SDLK_d))
        {
            move(glm::vec3(1, 0, 0));
        }
        if (windowManager->isKeyPressed(SDLK_q))
        {
            move(glm::vec3(-1, 0, 0));
        }
    }
}

