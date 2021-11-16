#include <GL/glew.h>
#include <iostream>
#include<vector>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Geometry.hpp>
#include <rendering/Camera.hpp>
#include <rendering/TrackballCamera.hpp>
#include <rendering/EyesCamera.hpp>
#include <rendering/Texture.hpp>


using namespace glimac;
using namespace rendering;


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

float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "Temple_Fun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    Cube cube(2);

    //Cube skybox(2);
    std::vector<std::string> faces = 
    {
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/right.png",
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/left.png",
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/top.png",
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/bottom.png",
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/front.png",
        "/home/clara/Documents/Projet/Temple_Fun/assets/textures/back.png"
    };


    //EyesCamera camera;
    TrackballCamera trackball_camera;
    EyesCamera eyes_camera;
    Camera* camera = &eyes_camera;



    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    PathProgram pathProgram(applicationPath);
    SkyboxProgram skyboxProgram(applicationPath);

    
    glEnable(GL_DEPTH_TEST);

    //293897E TEST SKYBOX
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int cubemapTexture = loadCubemap(faces);


    //Création du VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    Texture ground("/home/clara/Documents/Projet/Temple_Fun/assets/textures/ground4.png");
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount()*sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Création de l'IBO avec les indices:
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.getVertexCount()*sizeof(int), cube.getIndexPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Application loop:
    bool done = false;
    while(!done) {

        glm::mat4 ViewMatrix = camera->getViewMatrix();      
        
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_c)){
                if (camera->getCameraType() == 0){
                    camera = &eyes_camera;
                }
                else{
                    camera = &trackball_camera;
                }
            }
        }
        glm::ivec2 mousePos_trackball = windowManager.getMousePosition();
        glm::ivec2 mousePos_eyes = glm::ivec2(0.0);

        // Event TrackBallCamera
        if(camera->getCameraType() == 0) {
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
            trackball_camera.moveFront(0.03);
            }
            else if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) trackball_camera.moveFront(-0.03);

            trackball_camera.rotateLeft( mousePos_trackball.y );
            trackball_camera.rotateUp( mousePos_trackball.x );
        }
        
        //Event EyesCamera
        else {
            if(windowManager.isKeyPressed(SDLK_s)) camera->moveFront(-0.1);
            if(windowManager.isKeyPressed(SDLK_z)) camera->moveFront(0.1);
            if(windowManager.isKeyPressed(SDLK_q)) camera->moveLeft(0.1);
            if(windowManager.isKeyPressed(SDLK_d)) camera->moveLeft(-0.1);
            if(windowManager.isKeyPressed(SDLK_i)) camera->rotateLeft(0.2);
            if(windowManager.isKeyPressed(SDLK_k)) camera->rotateUp(0.2);
            
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
                mousePos_eyes = windowManager.getMousePosition();
                float mousePosX = mousePos_eyes.x/800.0f - 0.5;
                float mousePosY = mousePos_eyes.y/600.0f - 0.5;
                
                camera->rotateLeft(-3*mousePosX);
                camera->rotateUp(-3*mousePosY);

            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);      
        
        pathProgram.m_Program.use();
        // Drawing of the hero as a cube       
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 1.2, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix)); 
        
        glUniformMatrix4fv(pathProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * ViewMatrix));
        glUniformMatrix4fv(pathProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glUniformMatrix4fv(pathProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawElements(GL_TRIANGLES, cube.getVertexCount(), GL_UNSIGNED_INT,0);

        // Drawing of the path
        for (int i = -1 ; i <= 1; i ++){
            for (int j = 0 ; j <= 25 ; j ++) {
                glm::mat4 newViewMatrix = camera->getViewMatrix();
                newViewMatrix = glm::translate(newViewMatrix, glm::vec3(2*i, 0, 2*j));
                newViewMatrix = glm::scale(newViewMatrix, glm::vec3(1, 0.2, 1));
                glm::mat4 newNormalMatrix = glm::transpose(glm::inverse(newViewMatrix));
                
                //animation of the path    
                newViewMatrix = glm::translate(newViewMatrix, glm::vec3(0, 0, -3*windowManager.getTime()));
                
                glUniformMatrix4fv(pathProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * newViewMatrix));
                glUniformMatrix4fv(pathProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(newViewMatrix));
                glUniformMatrix4fv(pathProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(newNormalMatrix));
                
                glBindTexture(GL_TEXTURE_2D, ground.getTextureId());
                glUniform1i(pathProgram.uTexture, 0);
                glDrawElements(GL_TRIANGLES, cube.getVertexCount(), GL_UNSIGNED_INT,0); 
            }
        }


            // SKYBOX
            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
            skyboxProgram.m_Program.use();
            glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
            glUniformMatrix4fv(skyboxProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix));
            glUniformMatrix4fv(skyboxProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(skyboxViewMatrix));
            
            glBindVertexArray(skyboxVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glUniform1i(skyboxProgram.uSkybox, 0);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS);

            
            

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
       

        
        windowManager.swapBuffers();
       
    }

    return EXIT_SUCCESS;
}
