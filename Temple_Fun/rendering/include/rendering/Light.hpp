/**
 * \file Light.hpp
 * \brief Declaration of the class Modeel
*/

#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include <rendering/Camera.hpp>
#include <rendering/Program.hpp>



namespace rendering{
/*! \class Light
   * \brief Class of Light
   *
   *  This class enables to manage the Lights
   */
class Light{

public: 
    Light() = default;

    /*!
     *  \brief Draw the Directionnal Light that comes from above
     *  \param camera The camera to get the ViewMatrix
     *  \param LightProgram The corresponding shader
     *  \param ProjMatrix The Projection Matrix
     *  \param NormalMatrix The Normal Matrix
     * 
     */
    void drawDirectionnal(rendering::Camera* camera, rendering::ShaderManager& LightProgram, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix);
    
    

    /*!
     *  \brief Draw the Ponctual Light that is attached to the player
     *  \param camera The camera to get the ViewMatrix
     *  \param LightProgram The corresponding shader
     *  \param ProjMatrix The Projection Matrix
     *  \param NormalMatrix The Normal Matrix
     *  \param coord Coordinates of the light
     * 
     */
    void drawPonctual(const rendering::Camera* camera, rendering::ShaderManager& LightProgram, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, glm::vec3 coord);



};
}

#endif