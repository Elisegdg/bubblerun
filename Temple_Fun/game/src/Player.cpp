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

