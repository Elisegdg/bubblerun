#include "../include/game/CourseMap.hpp"
#include "../include/game/Object.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glimac/glm.hpp>
#include<rendering/Program.hpp>
#include <rendering/Camera.hpp>
#include <rendering/Texture.hpp>
#include <rendering/Model.hpp>
#include <rendering/Cube.hpp>


void CourseMap::addObject(int r,int g,int b)
{
    if(r==255 & g==255 & b==255 )
    {
        m_CourseMap.push_back(new Empty);

    }

    else if(r==255 & g==255)
    {
        m_CourseMap.push_back(new Up);
        m_PathVec.push_back(new Up);
    }
    else if(r==255 & b==255)
    {
        m_CourseMap.push_back(new Down);
        m_PathVec.push_back(new Down);    
    }
    else if (r==255)
    {
        m_CourseMap.push_back(new Straight);
        m_PathVec.push_back(new Straight);
    
    }
    else if (b==255)
    {
        m_CourseMap.push_back(new Right);
        m_PathVec.push_back(new Right);
    }
    else if (g==255)
    {
        m_CourseMap.push_back(new Left);
        m_PathVec.push_back(new Left);
    }

    
    else
    {
        m_CourseMap.push_back(new Obstacle);
        m_ObstacleVec.push_back(new Obstacle());
    }

    
}

void CourseMap::loadMap(const glimac::FilePath &file)
{
    std::ifstream fileMap(file);

    if (fileMap.fail())
    {
        std::cout<<"erreur de chargement"<<std::endl;
        return;
    }

    if (file.ext() != "ppm")
    {
        std::cout<<"pas le bon type de fichier"<<std::endl;
        return;
    }

    std::string line;
    getline(fileMap,line);
    getline(fileMap,line);
    
    fileMap >> m_sizex >>m_sizey;



    int r,g,b;

    fileMap>>r;

    int iterator = 0;

    for (int i = 0; i < m_sizey; i++)
    {
        for(int j=0;j<m_sizex;j++)
        {
            
            fileMap >>r;
            fileMap >>g;
            fileMap >>b;

            
            addObject(r,g,b);
            m_CourseMap[iterator]->addCoord(j,i,0);
            //m_PathVec[iterator]->addCoord(j,i,0);
            //m_ObstacleVec[iterator]->addCoord(j,i,0);
            
            iterator ++;

            
            
            
            
        }
        

    }

    // for (int i = 0; i < m_sizex; i++)
    // {
    //     m_CourseMap[i]->draw();
    //     std::cout<<m_CourseMap[i]->GetCoord()<<std::endl;
    // }
    

    

    
    // Object* objet = findObject(glm::vec3(2,0,0));
    // std::cout<<std::endl;
    // objet->draw();
    
    

}


Object* CourseMap::findObject(glm::vec3 coord)
{
    Object *ptrObj = nullptr;
    float m;
    bool trv = false;
    int deb = 1;
    int fin = m_sizex*m_sizey;
    
    while(!trv & deb <= fin)
    {
        
        
        m = floor((deb+fin)/2);
    
        if (m_CourseMap[m]->getCoord() == coord) 
        {
            
            trv = true;

        }

        
        else if(coord.y>m_CourseMap[m]->getCoord().y ||(coord.y==m_CourseMap[m]->getCoord().y && coord.x>m_CourseMap[m]->getCoord().x))
        {
            deb = m+1;
        }
        else if(coord.y<m_CourseMap[m]->getCoord().y ||(coord.y==m_CourseMap[m]->getCoord().y && coord.x<m_CourseMap[m]->getCoord().x))
        {
            fin = m-1;
        }

        
    }
    ptrObj = m_CourseMap[m];

    return m_CourseMap[m];


}


glm::vec3 CourseMap::start()
{
    int i =0; 
    while (m_CourseMap[i]->getName()!="straight")
    {
    
        i++;
    }
   
    return glm::vec3(i+1,0,0);
}

int CourseMap::end()
{
    return m_sizey -1;
}



void CourseMap::drawMap(rendering::Cube* mesh, const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager* windowManager) const
{
        for(int i = 0 ; i< m_CourseMap.size(); i++){
            if(m_CourseMap[i]->getName() != "obstacle"){
                m_CourseMap[i]->draw(mesh, camera, Program, ProjMatrix, m_sizey, windowManager);
            }
            
        }       
    
}

void CourseMap::drawObstacle(rendering::Cube* mesh, const rendering::Camera* camera, rendering::ShaderManager* Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager* windowManager) const
{
        for(int i = 0 ; i< m_CourseMap.size(); i++){
            if(m_CourseMap[i]->getName() == "obstacle"){
                m_CourseMap[i]->draw(mesh, camera, Program, ProjMatrix, m_sizey, windowManager);
            }
            
        }       
    
}
