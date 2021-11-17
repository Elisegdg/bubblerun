#include "../include/game/parcours.hpp"
#include "../include/game/object.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glimac/glm.hpp>


void Parcours::addObject(int r,int g,int b)
{
    if(r==255 & g==255 & b==255 )
    {
        m_parcours.push_back(new Empty);

    }

    else if (r==255)
    {
        m_parcours.push_back(new Straight);

    
    }
    else if (b==255)
    {
        m_parcours.push_back(new Right);
    }
    else if (g==255)
    {
        m_parcours.push_back(new Left);
    }
    else
    {
        m_parcours.push_back(new Obstacle);
    }

    
}

void Parcours::loadMap(const glimac::FilePath &file)
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

            std::cout << r <<" "<<g<<" "<<b<<std::endl;
    
            
            addObject(r,g,b);
            m_parcours[iterator]->AddCoord(j,i,0);
            m_parcours[iterator]->Draw();
            std::cout<<m_parcours[iterator]->GetCoord()<<std::endl;
            
            
            iterator ++;

            
            
            
            
        }
        

    }

    // for (int i = 0; i < m_sizex; i++)
    // {
    //     m_parcours[i]->Draw();
    //     std::cout<<m_parcours[i]->GetCoord()<<std::endl;
    // }
    

    

    
    Object* objet = FindObject(glm::vec3(3,0,0));
    std::cout<<std::endl;
    objet->Draw();
    
    

}


Object* Parcours::FindObject(glm::vec3 coord)
{
    Object *ptrObj = nullptr;
    float m;
    bool trv = false;
    int deb = 1;
    int fin = m_sizex*m_sizey;
    
    while(!trv & deb <= fin)
    {
        
        
        m = floor((deb+fin)/2);
    
        if (m_parcours[m]->GetCoord() == coord) 
        {
            
            trv = true;

        }

        
        else if(coord.y>m_parcours[m]->GetCoord().y ||(coord.y==m_parcours[m]->GetCoord().y && coord.x>m_parcours[m]->GetCoord().x))
        {
            deb = m+1;
        }
        else if(coord.y<m_parcours[m]->GetCoord().y ||(coord.y==m_parcours[m]->GetCoord().y && coord.x<m_parcours[m]->GetCoord().x))
        {
            fin = m-1;
        }

        
    }
    ptrObj = m_parcours[m];
    std::cout<<std::endl;
    m_parcours[m]->Draw();

    return m_parcours[m];


}

