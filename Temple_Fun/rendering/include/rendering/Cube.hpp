/**
 * \file Cube.hpp
 * \brief Declaration of the class Cube
*/



#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <rendering/Model.hpp>

namespace rendering{

/*! \class Cube
   * \brief Class of Cube
   *
   *  This class enables to create a cube-shaped mesh.
   */
class Cube : public Model{

public:
    /*!
    *  \brief Constructor of the Cube class
    *  \param texture The texture of the cube
    *  \param size The size of the cube
    */
    Cube(rendering::Texture texture, float size) : Model(texture) {
        build(size);
    }

    /*!
    *  \brief Destructor of the Cube class
    */
    ~Cube() = default;

    /*!
    *  \brief Fills the vertices vector of the cube
    */
    void build(const float &size);

};
}

#endif