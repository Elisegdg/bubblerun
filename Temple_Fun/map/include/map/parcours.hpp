#pragma once 

#include <vector>
#include <fstream> 
#include <iostream>
#include <glimac/FilePath.hpp>
#include "object.hpp"

class Parcours
{
private:
    std::vector<Object> m_parcours;
    int m_sizex; 
    int m_sizey; 

public:
    Object addObject(int r,int g,int b,float x,float y);
    void loadMap(const glimac::FilePath &file);
};

