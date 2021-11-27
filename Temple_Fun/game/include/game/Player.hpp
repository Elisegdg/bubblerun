
#pragma once 
#include <glimac/glm.hpp>
#include "../include/game/CourseMap.hpp"
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>
#include <rendering/Model.hpp>

class Player
{
private:
    glm::vec3 m_coord;
    unsigned int m_coins;
    bool m_life;
public:
    Player(CourseMap CourseMap):m_coord(CourseMap.start()),m_coins(0),m_life(true){}
    ~Player() = default;
    void setCoord(glm::vec3 coord);
    glm::vec3 getCoord();
    void addCoins();
    int getCoins();
    bool isLife();
    void setLife();
    void move(glm::vec3 coord_add);
    glm::vec3 convertCoord();
    void draw(rendering::Model* mesh, rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix);
};