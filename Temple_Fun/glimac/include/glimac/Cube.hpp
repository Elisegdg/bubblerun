#ifndef _CUBE_HPP
#define _CUBE_HPP

#include <vector>

#include "common.hpp"

namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Cube {


private:
    std::vector<ShapeVertex> m_Vertices;
    std::vector<int> m_index_ibo;
    GLsizei m_nVertexCount;

    // Alloue et construit les données (implantation dans le .cpp)
    void build(const float &size);
    

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cube(const float &size){
        build(size); // Construction des vertices (voir le .cpp)
    }
    Cube(const glm::vec3 &size);

    //destructeur
    ~Cube() = default;

    //Méthodes

    // Renvoie le pointeur vers les données
    const ShapeVertex* getDataPointer() const;
    GLsizei getVertexCount() const;
    const int* getIndexPointer() const;

};
    
}

#endif