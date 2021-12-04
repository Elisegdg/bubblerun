#include <GL/glew.h>
#include <iostream>
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
#include <game/CourseMap.hpp>
#include <game/Object.hpp>
#include <game/Player.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  


using namespace glimac;
using namespace rendering;

unsigned int VAO, VBO;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;

void RenderText(ShaderManager &s, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    s.use();
    glUniform3f(glGetUniformLocation(s.getId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

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


   
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "../Temple_Fun/assets/fonts/Poppins-Light.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return -1;
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        Characters.insert(std::pair<char, Character>(c, character));
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
   
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
        RenderText(TextProgram, "AQUA RUN", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        RenderText(TextProgram, "Score", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

        glDisable(GL_BLEND);


        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}