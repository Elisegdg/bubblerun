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



class Parcours
{
private:
    std::vector<Object *> m_parcours;
    int m_sizex; 
    int m_sizey; 

public:
    void addObject(int r,int g,int b);
    void loadMap(const glimac::FilePath &file);
    Object* findObject(glm::vec3 coord);
    int getSize();
    void drawMap(rendering::Cube* mesh, rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix);
};

#endif