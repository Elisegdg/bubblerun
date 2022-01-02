/**
 * \file Program.hpp
 * \brief Declaration of the class ShaderManager
*/

#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP


#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include<map>


namespace rendering{

/*! \class ShaderManager
   * \brief Class of ShaderManager
   *
   *  This class enables to manage the shaders and their uniform variables
   */
class ShaderManager{

private:
    glimac::Program m_program; 
    glimac::FilePath m_vsPath; /*!< Filepath of the vertex shader*/
    glimac::FilePath m_fsPath; /*!< Filepath of the fragment shader*/
    std::map<std::string, GLint> m_uniformVars; /*!< Map of the uniform variables */

public:

    /*!
    *  \brief Default Constructor of the ShaderManager class
    */
    ShaderManager() = default;

    /*!
    *  \brief Constructor of the ShaderManager class
    *  \param applicationPath Filepath of the program
    *  \param vs Filepath of the vertex shader
    *  \param fs Filepath of the fragment shader 
    */
    ShaderManager(const glimac::FilePath& applicationPath, const glimac::FilePath &vs, const glimac::FilePath &fs):
        m_vsPath(vs), m_fsPath(fs), m_program(glimac::loadProgram(applicationPath.dirPath() + vs, 
                                                                applicationPath.dirPath() +fs))
        {}

    ShaderManager(const ShaderManager &copy){
        
    }

    /*!
    *  \brief Destructor of the ShaderManager class
    */
    ~ShaderManager() = default;

    /*!
    *  \brief Getter of the program Id
    */
    GLuint getId() {
        return m_program.getGLId();
    }

    /*!
    *  \brief Add a uniform variable to the map
    *  \param name Name of the variable that needs to be added
    */
    void addUniform(const std::string &name){
        GLint uName = glGetUniformLocation(getId(), name.c_str());
        m_uniformVars.insert(std::pair<std::string, GLint>(name, uName));
    }

    /*!
    * \brief Sends a uniform variable of type mat4
    * \param name : the name of the uniform variable
    * \param value : the value to send
    */
    void uniformMatrix4fv(std::string name, glm::mat4 value){
        glUniformMatrix4fv(m_uniformVars[name], 1, GL_FALSE, glm::value_ptr(value));
    }

    /*!
    * \brief Sends a uniform variable of type mat3
    * \param name : the name of the uniform variable
    * \param value : the value to send
    */
    void uniformMatrix3fv(std::string name, glm::mat3 value){
        glUniformMatrix3fv(m_uniformVars[name], 1, GL_FALSE, glm::value_ptr(value));
    }

    /*!
    * \brief Sends a uniform variable of type int
    * \param name : the name of the uniform variable
    * \param value : the value to send
    */
    void uniform1i(std::string name, int value){
        glUniform1i(m_uniformVars[name], value);
    }

    /*!
    * \brief Sends a uniform variable of type vec3
    * \param name : the name of the uniform variable
    * \param value : the value to send
    */
    void uniform3f(std::string name,float value1,float value2,float value3)
    {
        glUniform3f(m_uniformVars[name],value1,value2,value3);

    }
    

    /*!
    * \brief Enables to use a shader
    */
    void use(){
        m_program.use();
    }

};

}


#endif