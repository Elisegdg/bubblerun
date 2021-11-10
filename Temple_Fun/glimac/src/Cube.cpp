#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac
{

    void Cube::build(const float &size)
    {

        float halfSize = size / 2.;

        // FRONT FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        // BACK FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        // RIGHT FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        // LEFT FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0, 1)}); // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0, 1)});   // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(0, 0)}); // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)});   // BOTTOM LEFT

        // UPPER FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(1, 1)}); // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)});   // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(1, 0)});    // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)}); // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(1, 0)});  // BOTTOM LEFT

        // BOTTOM FACE
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(1, 1)}); // TOP LEFT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0, 1)});   // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)});   // BOTTOM LEFT

        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0, 1)}); // TOP RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT
        m_Vertices.push_back((ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT

        m_nVertexCount = 36;
    }

    const ShapeVertex* Cube::getDataPointer() const
    {
        return &m_Vertices[0];
    }

    GLsizei Cube::getVertexCount() const
    {
        return m_nVertexCount;
    }

}