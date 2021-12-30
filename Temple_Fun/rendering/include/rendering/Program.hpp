#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP


#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <vector>
#include<map>


namespace rendering{

class ShaderManager{

private:
    glimac::Program m_program;
    glimac::FilePath m_vsPath;
    glimac::FilePath m_fsPath;
    std::map<std::string, GLint> m_uniformVars;

public:
    ShaderManager() = default;

    ShaderManager(const FilePath& applicationPath, const glimac::FilePath &vs, const glimac::FilePath &fs):
        m_vsPath(vs), m_fsPath(fs), m_program(glimac::loadProgram(applicationPath.dirPath() + vs, 
                                                                applicationPath.dirPath() +fs))
        {}

    ShaderManager(const ShaderManager &copy){
        
    }
    ~ShaderManager() = default;

    GLuint getId() const {
        return m_program.getGLId();
    }

    void addUniform(const std::string &name){
        GLint uName = glGetUniformLocation(getId(), name.c_str());
        m_uniformVars.insert(std::pair<std::string, GLint>(name, uName));
    }

    void uniformMatrix4fv(std::string name, glm::mat4 value) {
        glUniformMatrix4fv(m_uniformVars[name], 1, GL_FALSE, glm::value_ptr(value));
    }


    void uniform1i(std::string name, int value){
        glUniform1i(m_uniformVars[name], value);
    }

    void use(){
        m_program.use();
    }


};


}


#endif