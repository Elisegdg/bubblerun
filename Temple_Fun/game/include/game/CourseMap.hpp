#pragma once 

#include <vector>
#include <fstream> 
#include <iostream>
#include <glimac/FilePath.hpp>
#include "Object.hpp"

class Parcours
{
private:
    std::vector<Object *> m_parcours;
    int m_sizex; 
    int m_sizey; 

public:
    void addObject(int r,int g,int b);
    void loadMap(const glimac::FilePath &file);
    Object* FindObject(glm::vec3 coord);

};

