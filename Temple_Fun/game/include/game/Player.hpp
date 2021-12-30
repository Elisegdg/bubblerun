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
    bool m_isJumping;

public:

    Player(CourseMap CourseMap, glm::vec3 initialPos):m_coord(initialPos),m_coins(0),m_life(true),m_orientation(0), m_isJumping(false){}
    ~Player() = default;

    void setCoord(glm::vec3 coord);
    glm::vec3 getCoord() const;
    glm::vec3 getFloorCoord() const;
    glm::vec3 convertCoord()const ;

    void addCoins();
    int getCoins() const;

    bool isLife() const;
    void setLife();

    void move(glm::vec3 coord_add);
    void moveOrientation();
    void setOrientation(float orientatioin);
    float getOrientation();
    void moveside(glimac::SDLWindowManager& windowManager, bool& repeat);
    void jump(glimac::SDLWindowManager& windowManager, bool& repeat, int &step);
    void fall(int &step);
    bool isJumping() const;
    void setJump(glimac::SDLWindowManager &windowManager, bool &repeat);
    void moveManager(Object* objet, glimac::SDLWindowManager& windowManager, bool& repeat, rendering::Camera* camera);
    void moveEnemyManager(Object* objet_enemy);
    void draw(rendering::Model& mesh, rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix);

};






#endif