#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <glimac/glm.hpp>
#include "../include/game/CourseMap.hpp"
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>
#include <rendering/Model.hpp>
#include <glimac/SDLWindowManager.hpp>




class Player
{
private:
    glm::vec3 m_coord;
    unsigned int m_coins;
    bool m_life;
    float m_orientation;

public:
    Player(CourseMap CourseMap):m_coord(CourseMap.start()),m_coins(0),m_life(true),m_orientation(0){}
    ~Player() = default;
    void setCoord(glm::vec3 coord);
    glm::vec3 getCoord();
    void addCoins();
    int getCoins();
    bool isLife();
    void setLife();
    void move(glm::vec3 coord_add);
    void moveOrientation();
    void setOrientation(float orientatioin);
    float getOrientation();
    void moveside(glimac::SDLWindowManager& windowManager, bool& repeat);
    void jump(glimac::SDLWindowManager& windowManager, bool& repeat);
    void fall();


    glm::vec3 convertCoord();
    void draw(rendering::Model& mesh, rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix);
};






#endif