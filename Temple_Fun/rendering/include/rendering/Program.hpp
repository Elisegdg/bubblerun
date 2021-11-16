#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP


#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

struct PathProgram{
    Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    PathProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {

        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct SkyboxProgram{
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uSkybox;

    SkyboxProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/skybox.vs.glsl",
                              applicationPath.dirPath() + "shaders/skybox.fs.glsl")) {

        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "projection");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "view");
        uSkybox = glGetUniformLocation(m_Program.getGLId(), "uSkybox");
        }
};

#endif