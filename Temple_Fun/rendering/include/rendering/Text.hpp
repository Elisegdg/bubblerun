#pragma once 
#include <iostream>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H  



namespace rendering{
class Text
{
private:
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
    
public:
    Text()=default;
    ~Text()=default;
    unsigned int getTextureID()
    {
        return TextureID;
    }  

    glm::ivec2   getSize()
    {
        return Size;
    }  

    glm::ivec2   getBearing()
    {
        return Bearing;
    } 

    unsigned int getAdvance()
    {
        return Advance;
    }

    void loadFont(std::map<char, Text> &Characters)
    {

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        }

        FT_Face face;
        if (FT_New_Face(ft, "../Temple_Fun/assets/fonts/Findet Nemo.ttf", 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        }
        FT_Set_Pixel_Sizes(face, 0, 48);
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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
            // now store character for later use
            Text character;
            character.TextureID = texture;
            character.Size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            character.Bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            character.Advance = face->glyph->advance.x;
            Characters.insert(std::pair<char, Text>(c, character));
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
    void RenderText(GLuint &id,std::map<char, Text> &Characters, std::string text, float x, float y, float scale, glm::vec3 color,unsigned int VAO,unsigned int VBO)
    {
        // activate corresponding render state
        glUniform3f(glGetUniformLocation(id, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Text ch = Characters[*c];

            float xpos = x + ch.getBearing().x * scale;
            float ypos = y - (ch.getSize().y - ch.getBearing().y) * scale;

            float w = ch.getSize().x * scale;
            float h = ch.getSize().y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos, ypos, 0.0f, 1.0f},
                {xpos + w, ypos, 1.0f, 1.0f},

                {xpos, ypos + h, 0.0f, 0.0f},
                {xpos + w, ypos, 1.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 0.0f}};
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.getTextureID());
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.getAdvance() >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};


}