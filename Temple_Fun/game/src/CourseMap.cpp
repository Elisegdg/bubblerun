#include "../include/game/CourseMap.hpp"
#include "../include/game/Object.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glimac/glm.hpp>
#include <rendering/Program.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Texture.hpp>
#include <rendering/Model.hpp>
#include <rendering/Cube.hpp>
#include <rendering/Light.hpp>
#include <random>
#include <iostream>
#include <functional>
#include <chrono>

namespace game {
void CourseMap::addObject(int r, int g, int b)
{
    if (r == 255 & g == 255 & b == 255)
    {
        m_CourseMap.Add(new Empty);
    }

    else if (r == 255 & g == 255)
    {
        m_CourseMap.Add(new Up);
    }
    else if (r == 255 & b == 255)
    {
        m_CourseMap.Add(new Down);
    }
    else if (r == 255)
    {
        m_CourseMap.Add(new Straight(false));
    }
    else if (b == 255)
    {
        m_CourseMap.Add(new Right);
    }
    else if (g == 255)
    {
        m_CourseMap.Add(new Left);
    }

    else
    {
        m_CourseMap.Add(new Obstacle);
    }
}

void CourseMap::clearCourseMap(){
        Iterator<Object*, Container<Object*>> *it = m_CourseMap.CreateIterator();
        for (it->First(); !it->IsDone(); it->Next())
        {
            delete (*it->Current());
            (*it->Current()) = nullptr;
        }
}

void CourseMap::loadMap(const glimac::FilePath &file)
{
    std::ifstream fileMap(file);

    if (fileMap.fail())
    {
        throw std::string("Loading of the map failed");
        return;
    }

    assert((file.ext() == "ppm") && "Error : please load a .ppm file");
    

    std::string line;
    getline(fileMap, line);
    getline(fileMap, line);

    fileMap >> m_sizex >> m_sizey;

    int r, g, b;

    fileMap >> r;

    int iterator = 0;

    for (int i = 0; i < m_sizey; i++)
    {
        for (int j = 0; j < m_sizex; j++)
        {

            fileMap >> r;
            fileMap >> g;
            fileMap >> b;

            addObject(r, g, b);
            m_CourseMap[iterator]->addCoord(j, i, 0);

            iterator++;
        }
    }
}

Object *CourseMap::findObject(glm::vec3 coord)
{
    Object *ptrObj = nullptr;
    float m;
    bool trv = false;
    int deb = 1;
    int fin = m_sizex * m_sizey;

    while (!trv & deb <= fin)
    {

        m = floor((deb + fin) / 2);

        if (m_CourseMap[m]->getCoord().x == coord.x & m_CourseMap[m]->getCoord().y == coord.y)
        {

            trv = true;
        }

        else if (coord.y > m_CourseMap[m]->getCoord().y || (coord.y == m_CourseMap[m]->getCoord().y && coord.x > m_CourseMap[m]->getCoord().x))
        {
            deb = m + 1;
        }
        else if (coord.y < m_CourseMap[m]->getCoord().y || (coord.y == m_CourseMap[m]->getCoord().y && coord.x < m_CourseMap[m]->getCoord().x))
        {
            fin = m - 1;
        }
    }
    ptrObj = m_CourseMap[m];

    return m_CourseMap[m];


}

glm::vec3 CourseMap::start()
{
    int i = 0;
    while (m_CourseMap[i]->getName() != "straight")
    {

        i++;
    }

    return glm::vec3(i + 1, 0, 0);
}

int CourseMap::end() const
{
    return m_sizey - 1;
}

void CourseMap::drawMap(rendering::Cube &mesh_path, rendering::Model &mesh_coin, const rendering::Camera *camera, rendering::ShaderManager &Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager &windowManager)
{
    Iterator<Object*, Container<Object*>> *it = m_CourseMap.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
    {
        if ((*it->Current())->getName() != "obstacle")
        {
            (*it->Current())->draw(mesh_path, camera, Program, ProjMatrix, windowManager);
        }
        if ((*it->Current())->getIfCoins())
        {
            (*it->Current())->drawCoins(mesh_coin, camera, Program, ProjMatrix, windowManager);
        }
    }
    delete it;

}

void CourseMap::drawObstacle(rendering::Cube &mesh, const rendering::Camera *camera, rendering::ShaderManager &Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager &windowManager) 
{
    Iterator<Object*, Container<Object*>> *it = m_CourseMap.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
    {
        if ((*it->Current())->getName() == "obstacle")
        {
            (*it->Current())->draw(mesh, camera, Program, ProjMatrix, windowManager);
        }
    }
    delete it;
}


void CourseMap::loadCoins()
{
    Iterator<Object*, Container<Object*>> *it = m_CourseMap.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
        if ((*it->Current())->getName() == "straight")
        {
            std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<int>distrib{0,1};    
            (*it->Current())->setCoins(distrib(re));
        }
    delete it; 
    }
    
}
