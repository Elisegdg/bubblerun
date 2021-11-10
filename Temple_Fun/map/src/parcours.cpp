#include "../include/map/parcours.hpp"
#include "../include/map/object.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Object Parcours::addObject(int r,int g,int b,float x,float y)
{
    
    if (r==255 & g==0 & b==0)
    {
        std::cout<<"  droit  ";
        Object droit;
        return droit;
    }
    if (r==0 & g==255 & b==0)
    {
        std::cout<<"  droite  ";
        Object droite;
        return droite;
    }
    if (r==0 & g==0 & b==255)
    {
        std::cout<<"  gauche  ";
        Object gauche;
        return gauche;
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
    std::cout<<"size x "<<m_sizex<<std::endl;
    std::cout<<"size y "<<m_sizey<<std::endl;

    getline(fileMap,line);
    getline(fileMap,line);

    int r,g,b;

    for (int i = 0; i < m_sizex; i++)
    {
        for(int j=0;j<m_sizey;j++)
        {
            
            fileMap >>r;
            fileMap >>g;
            fileMap >>b;
    
            if (r!=255 || g!=255 || b!=255)
            {
                m_parcours.push_back(addObject(r,g,b, i, j));
            }
            
            
        }
        

    }
    

    

}

