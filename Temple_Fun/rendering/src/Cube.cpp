#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "rendering/Cube.hpp"


namespace rendering{
void Cube::build(const float &size)
    {

        float halfSize = size / 2.;

        // FRONT FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT


        // BACK FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT


        // RIGHT FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 1)});     // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT


        // LEFT FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(-halfSize, halfSize, halfSize), glm::vec2(1, 1)});   // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(0, 1)}); // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)}); // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(0, 0)}); // BOTTOM RIGHT

        // UP FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, -halfSize), glm::vec3(-halfSize, halfSize, -halfSize), glm::vec2(1, 1)}); // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, -halfSize), glm::vec3(halfSize, halfSize, -halfSize), glm::vec2(0, 1)});   // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(1, 0)});    // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, halfSize, halfSize), glm::vec3(halfSize, halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT

        // BOTTOM FACE
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec3(-halfSize, -halfSize, -halfSize), glm::vec2(1, 1)}); // TOP LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, -halfSize), glm::vec3(halfSize, -halfSize, -halfSize), glm::vec2(0, 1)});   // TOP RIGHT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(-halfSize, -halfSize, halfSize), glm::vec3(-halfSize, -halfSize, halfSize), glm::vec2(1, 0)});   // BOTTOM LEFT
        m_vertices.push_back((glimac::ShapeVertex){glm::vec3(halfSize, -halfSize, halfSize), glm::vec3(halfSize, -halfSize, halfSize), glm::vec2(0, 0)});   // BOTTOM RIGHT

        m_vertexCount = 36;

        m_index = {0,1,2,1,2,3,         //FRONT FACE
                       4,5,6,5,6,7,         //BACK FACE
                       8,9,10,9,10,11,      //RIGHT FACE
                       12,13,14,13,14,15,   //LEFT FACE
                       16,17,18,17,18,19,   //UP FACE
                       20,21,22,21,22,23    //BOTTOM FACE
                       };  
    }
}