
#include "../include/game/Player.hpp"
#include "../include/game/CourseMap.hpp"
#include <glimac/glm.hpp>

void Player::setCoord(glm::vec3 coord)
{
    m_coord = coord;
}

glm::vec3 Player::getCoord() const
{
    return m_coord;
}
glm::vec3 Player::getFloorCoord() const
{

    return glm::vec3(floor(m_coord.x), floor(m_coord.y), floor(m_coord.z));
}

void Player::addCoins()
{
    m_coins++;
}

int Player::getCoins() const
{
    return m_coins;
}

bool Player::isLife() const
{
    return m_life;
}

void Player::move(glm::vec3 coord_move)
{
    m_coord = glm::vec3(m_coord[0] + coord_move[0], m_coord[1] + coord_move[1], m_coord[2] + coord_move[2]);
}

void Player::setLife()
{
    m_life = false;
}

glm::vec3 Player::convertCoord() const
{
    return glm::vec3(getCoord().x - 1., getCoord().z, getCoord().y);
}

void Player::draw(rendering::Model &mesh, rendering::Camera *camera, rendering::ShaderManager &Program, glm::mat4 ProjMatrix)
{

    glm::mat4 ViewMatrix = camera->getViewMatrix();
    ViewMatrix = glm::translate(ViewMatrix, convertCoord());
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0.6, 0));

    ViewMatrix = glm::scale(ViewMatrix, glm::vec3(1, 1, 1));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

    Program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
    Program.uniformMatrix4fv("uMVMatrix", ViewMatrix);
    Program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    Program.uniform1i("uTexture", 0);

    mesh.draw();
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

void Player::moveside(glimac::SDLWindowManager &windowManager, bool &repeat)
{
    if (m_orientation == 0.)
    {

        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            SDL_EnableKeyRepeat(0, 0);

            repeat = false;
            move(glm::vec3(-1., 0, 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            move(glm::vec3(1., 0, 0));
        }
    }
    if (m_orientation == 90.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            move(glm::vec3(0, 1., 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            move(glm::vec3(0, -1., 0));
        }
    }

    if (m_orientation == -90.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            move(glm::vec3(0, -1., 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
            move(glm::vec3(0, 1., 0));
        }
    }

    if (m_orientation == 180.)
    {
        if (windowManager.isKeyPressed(SDLK_d) && repeat)
        {
            repeat = false;
            move(glm::vec3(1., 0, 0));
        }
        if (windowManager.isKeyPressed(SDLK_q) && repeat)
        {
            repeat = false;
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

bool Player::isJumping() const
{
    return m_isJumping;
}

void Player::moveManager(Object *objet, glimac::SDLWindowManager &windowManager, bool &repeat, rendering::Camera *camera)
{
    if (objet->getIfCoins() & !m_isJumping)
    {
        objet->removeCoin();
    }
    if (objet->getName() == "straight")
    {
        moveside(windowManager, repeat);
        setJump(windowManager, repeat);
    }

    if (objet->getName() == "up")
    {
        setCoord(objet->getCoord());
        setOrientation(180.);
        move(glm::vec3(0, -1, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "down")
    {
        setCoord(objet->getCoord());
        setOrientation(0.);
        move(glm::vec3(0, 1, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "right")
    {
        setCoord(objet->getCoord());
        setOrientation(90.);
        move(glm::vec3(1, 0, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "left")
    {
        setCoord(objet->getCoord());
        setOrientation(-90.);
        move(glm::vec3(-1, 0, 0));
        camera->rotateLeft(getOrientation());
    }

    if (objet->getName() == "empty" & getCoord()[2] < 0.3)
    {
        setLife();
        std::cout << "oops, you fell" << std::endl;
    }

    if (objet->getName() == "obstacle" & getCoord()[2] < 0.3)
    {
        setLife();
        std::cout << "oops you stumbled over an obstacle" << std::endl;
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