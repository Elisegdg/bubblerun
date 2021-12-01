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

void Player::moveside(char a )
{
    if (m_orientation == 0.)
    {
        if (a == 'd')
        {
            move(glm::vec3(-1, 0, 0));
        }
        if (a == 'q')
        {
            move(glm::vec3(1, 0, 0));
        }
    }
    if (m_orientation == 90.)
    {
        if (a == 'd')
        {
            move(glm::vec3(0, 1, 0));
        }
        if (a == 'q')
        {
            move(glm::vec3(0, -1, 0));
        }
    }
    if (m_orientation == -90.)
    {
        if (a == 'd')
        {
            move(glm::vec3(0, -1, 0));
        }
        if (a == 'q')
        {
            move(glm::vec3(0, 1, 0));
        }
    }
    if (m_orientation == 180.)
    {
        if (a == 'd')
        {
            move(glm::vec3(1, 0, 0));
        }
        if (a == 'q')
        {
            move(glm::vec3(-1, 0, 0));
        }
    }
}