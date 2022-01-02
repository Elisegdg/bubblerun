/**
 * \file CourseMap.hpp
 * \brief Declaration of the class CourseMap
*/


#ifndef _COURSEMAP_HPP
#define _COURSEMAP_HPP

#include <vector>
#include <fstream> 
#include <iostream>
#include <glimac/FilePath.hpp>
#include "Object.hpp"
#include <game/Iterator.hpp>
#include <rendering/Light.hpp>

/*! \namespace game
 *  \brief Our game library
 *
 *   Namespace regrouping the tools for the game engine
 */
namespace game {

/*! \class CourseMap
   * \brief Class of CourseMap
   *
   *  This class manages the Coursemap. It reads, loads and draws its data.
   */
class CourseMap
{
private:
    Container<game::Object *> m_CourseMap;  /*!< Container of the data of the coursemap. Use of the Iterator Design Pattern */
    int m_sizex;  /*!< size of the map (pixels) along the x axis */
    int m_sizey;  /*!< size of the map (pixels) along the y axis */

public:

    

    /*!
     *  \brief Fill the Container of objects.
     *  
     * According to the pixel color of the .ppm where the map is drawn, fill the CourseMap Container
     * with different object (Left, Right, Straight...)
     * 
     *  \param r Red component
     *  \param g Green component
     *  \param b Blue component
     *
     */
    void addObject(int r,int g,int b);

    /*!
     *  \brief Load the ppm file containing the map
     *
     *  \param file Filepath of the map (.ppm)
     */

    /*!
     *  \brief Free the memory
     *  
     * Deletes each pointer object that we created with a "new" in the addObject function.
     * 
     *
     */
    void clearCourseMap();

    void loadMap(const glimac::FilePath &file);

    /*!
     *  \brief Get the object at a certain coordinate
     *
     *  \param coord A vector of 3 coordinates
     * 
     *  \return the type of object located at coord
     */
    Object* findObject(glm::vec3 coord);

    /*!
     *  \brief Getter of the beginning of the path
     *
     *  \return the beginning of the path
     */
    glm::vec3 start();

    /*!
     *  \brief Getter of the finishing line
     *
     *  \return the finishing line
     */
    int end() const;

    /*!
     *  \brief Draw the map and the coins
     *
     *  \param mesh_path The mesh corresponding to the path
     *  \param mesh_coin The mesh corresponding to the coins
     *  \param camera The camera (to get the ViewMatrix)
     *  \param Program The shader
     *  \param ProjMatrix The Projection Matrix
     *  \param WindowManager The SDLWindowManager
     * 
     */
    void drawMap(rendering::Cube& mesh_path, rendering::Model & mesh_coin, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager) ;

    /*!
     *  \brief Draw the obstacles
     *
     *  \param mesh The mesh corresponding to the obstacle
     *  \param camera The camera (to get the ViewMatrix)
     *  \param Program The shader
     *  \param ProjMatrix The Projection Matrix
     *  \param WindowManager The SDLWindowManager 
     */
    void drawObstacle(rendering::Cube& mesh, const rendering::Camera* camera, rendering::ShaderManager& Program, glm::mat4 ProjMatrix, glimac::SDLWindowManager& windowManager) ;
    
    /*!
     *  \brief Load the coins and place them randomly
     *
     */


    void loadCoins();
};

}
#endif