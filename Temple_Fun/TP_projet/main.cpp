#include <GL/glew.h>
#include <iostream>
#include <map>
#include <vector>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>
#include <rendering/Camera.hpp>
#include <rendering/TrackballCamera.hpp>
#include <rendering/EyesCamera.hpp>
#include <rendering/Texture.hpp>
#include <rendering/Program.hpp>
#include <rendering/Skybox.hpp>
#include <rendering/Cube.hpp>
#include <rendering/Text.hpp>
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  


using namespace glimac;
using namespace rendering;

unsigned int VAO, VBO;



int main(int argc, char **argv)
{

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "Temple_Fun");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    std::map<char, Text> Characters;

    Text text;
    text.loadFont(Characters);
   
   
   /*********************************
    *     INITIALIZATION CODE       *
   *********************************/



    CourseMap map;
    map.loadMap("../Temple_Fun/assets/test_parcours.ppm");
    Texture ground("../Temple_Fun/assets/textures/ground4.png");
    Texture nemo("../Temple_Fun/assets/textures/nemo.jpg");
    Cube cube_path(ground,1);
    Cube cube_nemo(nemo, 1);

    TrackballCamera trackball_camera;
    EyesCamera eyes_camera;
    Camera *camera = &eyes_camera;

    Player player(map);

    Object* objet = map.findObject(player.getCoord()); 

    bool right = false;
    bool left = false;
    bool up = false;
    bool down = true;

    // Shaders loading
    FilePath applicationPath(argv[0]);
    
    ShaderManager TextureProgram(applicationPath, "shaders/3D.vs.glsl", "shaders/tex3D.fs.glsl");
    TextureProgram.addUniform("uMVPMatrix");
    TextureProgram.addUniform("uMVMatrix");
    TextureProgram.addUniform("uNormalMatrix");
    TextureProgram.addUniform("uTexture");

    ShaderManager SkyboxProgram(applicationPath, "shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl");
    SkyboxProgram.addUniform("projection");
    SkyboxProgram.addUniform("view");
    SkyboxProgram.addUniform("uSkybox");

    ShaderManager TextProgram(applicationPath, "shaders/text.vs.glsl", "shaders/text.fs.glsl");
    SkyboxProgram.addUniform("projection");

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    TextProgram.use();
    glUniformMatrix4fv(glGetUniformLocation(TextProgram.getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glEnable(GL_DEPTH_TEST);

    
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    

    // Creation of the Skybox
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    

    unsigned int cubemapTexture = loadCubemap(skybox_sky);

   //Creation of the cube used for the Player and the Path
    cube_path.setVbo();
    cube_path.setIbo();
    cube_path.setVao();

    cube_nemo.setVbo();
    cube_nemo.setIbo();
    cube_nemo.setVao();


    

    // Application loop:
    bool done = false;
    while (!done)
    {
        glm::mat4 ViewMatrix = camera->getViewMatrix();

        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; 
            }
            if (windowManager.isKeyPressed(SDLK_c))
            {
                if (camera->getCameraType() == 0)
                {
                    camera = &eyes_camera;
                }
                else
                {
                    camera = &trackball_camera;
                }
            }
        }

        camera->eventCamera(&windowManager);
        
        
        
        /*********************************
         *      RENDERING CODE           *
         *********************************/
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        //glBindVertexArray(vao);

    

        

        TextureProgram.use();

        // Drawing of the hero as a cube
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 2000.f / 1000.f, 0.1f, 100.f);

        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(1., 0.6, 0.));
        ViewMatrix = glm::scale(ViewMatrix, glm::vec3(0.5, 1.2, 0.5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));
        
        TextureProgram.uniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix);
        TextureProgram.uniformMatrix4fv("uMVMatrix", ViewMatrix);
        TextureProgram.uniformMatrix4fv("uNormalMatrix", NormalMatrix);

        cube_nemo.draw();

        // Drawing of the Path
        map.drawMap(&cube_path,camera, &TextureProgram, ProjMatrix, &windowManager);


        // Drawing of the Skybox
        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        SkyboxProgram.use();
        glm::mat4 skyboxViewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
        SkyboxProgram.uniformMatrix4fv("projection", ProjMatrix);
        SkyboxProgram.uniformMatrix4fv("view", skyboxViewMatrix);
        

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        SkyboxProgram.uniform1i("uSkybox", 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        TextProgram.use();
        GLuint id = TextProgram.getId();
        text.RenderText(id,Characters, "AQUA RUN", 25.0f, 25.0f, 1.0f, glm::vec3(0.87, 0.325f, 0.03f),VAO,VBO);
        text.RenderText(id,Characters, "Score", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f),VAO,VBO);

        glDisable(GL_BLEND);

        //222, 83, 9

        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}