#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <rendering/Model.hpp>

namespace rendering{
class Cube : public Model{

public:
    Cube(rendering::Texture texture, float size) : Model(texture) {
        build(size);
    }
    ~Cube() = default;
    void build(const float &size);

};
}

#endif