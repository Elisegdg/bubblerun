#pragma once 

#include <vector>
#include <fstream> 
#include <iostream>
#include <glimac/FilePath.hpp>
#include "Object.hpp"
#include <game/Iterator.hpp>

class CourseMap
{
private:
    Container<Object *> m_CourseMap;
    int m_sizex; 
    int m_sizey; 

public:
    void addObject(int r,int g,int b);
    void loadMap(const glimac::FilePath &file);
    Object* findObject(glm::vec3 coord);
    glm::vec3 start();
    int end();
    void drawMap(rendering::Cube& mesh_path, rendering::Cube& mesh_coin, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager) ;
    void drawObstacle(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager) ;

};

