#ifndef _ENEMY_HPP
#define _ENEMY_HPP

#include <game/Player.hpp>

class Enemy{
private: 
    Player* m_player;
    unsigned int m_distance;
public:
    Enemy(Player* playerToFollow, int distanceToPlayer=1):
        m_player(playerToFollow), m_distance(distanceToPlayer){}

};


#endif