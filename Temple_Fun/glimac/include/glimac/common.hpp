#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Vertex2DColor
{
    glm::vec3 position;
    glm::vec3 color;

    Vertex2DColor(){}
    Vertex2DColor(glm::vec3 position, glm::vec3 color):position(position), color(color){}
};


}
