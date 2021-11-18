#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <rendering/Model.hpp>

class Cube2 : public Model{

public:
    Cube2(rendering::Texture texture, float size) : Model(texture) {
        build(size);
    }
    void build(const float &size);

};

#endif