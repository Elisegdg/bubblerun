#pragma once 
#include <glimac/glm.hpp>

class Personnage
{
private:
    glm::vec3 m_coord;
    unsigned int coins;
public:
    Personnage() = default;
    ~Personnage() = default;
    void SetCoord(glm::vec3 coord);
    void GetCoord();
};

