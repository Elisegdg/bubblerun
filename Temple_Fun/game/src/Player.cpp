
#include "../include/game/Player.hpp"
#include "../include/game/CourseMap.hpp"
#include <glimac/glm.hpp>


namespace game{
void Player::setCoord(glm::vec3 coord)
{
    m_coord = coord;
}

glm::vec3 Player::getCoord()
{
    return m_coord;
}
glm::vec3 Player::getFloorCoord()
{
    return glm::vec3(floor(m_coord.x), floor(m_coord.y), m_coord.z);
}

void Player::addCoins()
{
    m_coins++;
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
    m_coord = glm::vec3(m_coord[0] + coord_move[0], m_coord[1] + coord_move[1], m_coord[2] + coord_move[2]);
}

void Player::setLife(bool life)
{
    m_life = life;
}

glm::vec3 Player::convertCoord()
{
    return glm::vec3(getCoord().x-2, getCoord().z, getCoord().y);
}

void Player::draw(rendering::Model &mesh, rendering::Camera *camera, rendering::ShaderManager &Program, glm::mat4 ProjMatrix)
{

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, convertCoord());
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0.6, 0));
    ViewMatrix = glm::rotate(ViewMatrix, getRotation(), glm::vec3(0.,1.,0.));
    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(1.3, 1.3, 1.3));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniform1i("uTexture", 0);
    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    
    mesh.draw();

    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindVertexArray(0);*/
}

void Player::moveOrientation()
{
    if (m_orientation == 0.)
    {
        move(glm::vec3(0, 0.1, 0));
    }
    if (m_orientation == 90.)
    {
        move(glm::vec3(0.1, 0, 0));
    }
    if (m_orientation == -90.)
    {
        move(glm::vec3(-0.1, 0, 0));
    }
    if (m_orientation == 180.)
    {
        move(glm::vec3(0, -0.1, 0));
    }
}

void Player::setOrientation(float orientation)
{
    m_orientation = orientation;
}

float Player::getOrientation()
{
    return m_orientation;
}

void Player::moveside(glimac::SDLWindowManager &windowManager, bool &repeat, bool &turn_up, bool &turn_down, bool &turn_right, bool &turn_left)
{
    if (m_orientation == 0.)
    {

        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            SDL_EnableKeyRepeat(0, 0);
            turn_left = true;
            repeat = false;
            move(glm::vec3(-1., 0, 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            turn_right = true;
            move(glm::vec3(1., 0, 0));
        }
    }
    if (m_orientation == 90.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            turn_down = true;
            move(glm::vec3(0, 1., 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            turn_up = true;
            move(glm::vec3(0, -1., 0));
        }
    }

    if (m_orientation == -90.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            turn_up = true;
            move(glm::vec3(0, -1., 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            turn_down = true;
            move(glm::vec3(0, 1., 0));
        }
    }

    if (m_orientation == 180.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            turn_right = true;

            move(glm::vec3(1., 0, 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            turn_left = true;
            move(glm::vec3(-1., 0, 0));
        }
    }
}

void Player::setJump(glimac::SDLWindowManager &windowManager, bool &repeat)
{
    if (windowManager.isKeyPressed(SDLK_z) && repeat)
    {
        m_isJumping = true;
        repeat = false;
    }
}

void Player::jump(glimac::SDLWindowManager &windowManager, bool &repeat, int &step)
{

    if (step < 10)
    {
        m_coord.z += 0.1;
        m_isJumping = true;
        moveOrientation();
        step++;
    }
}

void Player::fall(int &step)
{

    if (step < 20)
    {
        m_coord.z -= 0.1;

        moveOrientation();
        step++;
    }
    else
    {
        step = 0;
        m_isJumping = false;
    }
}

bool Player::isJumping()
{
    return m_isJumping;
}

void Player::moveManager(Object *objet, rendering::Camera *camera, int &score, glimac::SDLWindowManager &windowManager, bool &repeat, bool &turn_up, bool &turn_down, bool &turn_right, bool &turn_left, int &step_turn)
{
    if (objet->getIfCoins() & !m_isJumping)
    {
        objet->removeCoin();
        score += 50;
    }
    if (objet->getName() == "straight")
    {
        moveside(windowManager, repeat, turn_up, turn_down, turn_right, turn_left);
        setJump(windowManager, repeat);
    }

    if (objet->getName() == "up" & turn_up)
    {
        turn_up = false;
        step_turn = 0;
        setCoord(objet->getCoord());
        setOrientation(180.);
        move(glm::vec3(0, -1, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "down" & turn_down)
    {
        turn_down = false;
        step_turn = 0;
        setCoord(objet->getCoord());
        setOrientation(0.);
        move(glm::vec3(0, 1, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "right" & turn_right)
    {
        turn_right = false;
        step_turn = 0;
        setCoord(objet->getCoord());
        setOrientation(90.);
        move(glm::vec3(1, 0, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "left" & turn_left)
    {
        turn_right = false;
        step_turn = 0;
        setCoord(objet->getCoord());
        setOrientation(-90.);
        move(glm::vec3(-1, 0, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "empty" & getCoord()[2] < 0.3 || getCoord().x < 0)
    {
        setLife(false);
    }

    if (objet->getName() == "obstacle" & getCoord()[2] < 0.3)
    {
        setLife(false);
    }
}


void Player::moveEnemyManager(Object* objet_enemy)
{
    if (objet_enemy->getName() == "up")
    {
        setCoord(objet_enemy->getCoord());
        move(glm::vec3(0, -1, 0));
        setOrientation(180.);
    }

    if (objet_enemy->getName() == "down")
    {
        setCoord(objet_enemy->getCoord());
        move(glm::vec3(0, 1, 0));
        setOrientation(0.);
    }

    if (objet_enemy->getName() == "right")
    {
        setCoord(objet_enemy->getCoord());
        move(glm::vec3(1, 0, 0));
        setOrientation(90.);
    }

    if (objet_enemy->getName() == "left")
    {
        setCoord(objet_enemy->getCoord());
        move(glm::vec3(-1, 0, 0));
        setOrientation(-90.);
    }
}

}