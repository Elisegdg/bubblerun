#ifndef _COURSEMAP_HPP
#define _COURSEMAP_HPP

#include <vector>
#include <fstream> 
#include <iostream>
#include <glimac/FilePath.hpp>
#include "Object.hpp"
#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>
#include <rendering/Model.hpp>
#include <rendering/Cube.hpp>
#include <glimac/SDLWindowManager.hpp>



class Parcours
{
private:
    std::vector<Object *> m_parcours;
    int m_sizex; 
    int m_sizey; 

public:
    void addObject(const unsigned int r, const unsigned int g, const unsigned int b);
    void loadMap(const glimac::FilePath &file);
    Object* findObject(const glm::vec3 coord);
    void drawMap(rendering::Cube* mesh, const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager* windowManager)const;
};

#endif