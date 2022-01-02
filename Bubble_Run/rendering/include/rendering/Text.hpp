/**
 * \file Text.hpp
 * \brief Declaration of the class Text
*/

#ifndef _TEXT_HPP
#define _TEXT_HPP

#include <iostream>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H
#include <rendering/Score.hpp>

namespace rendering
{
    /*! \class Text
   * \brief Abstract class of Text
   *
   *  This class deals with displaying the text on the game window and menus.
   */
    class Text
    {
    private:
        unsigned int TextureID; /*!< ID handle of the glyph texture*/
        glm::ivec2 Size;        /*< Size of glyph*/
        glm::ivec2 Bearing;     /*< Offset from baseline to left/top of glyph*/
        unsigned int Advance;   /*< Offset to advance to next glyph*/
        GLuint m_vao, m_vbo; 

    public:
        /*!
        *  \brief Default Constructor of the Text class
        */
        Text() = default;

        /*!
        *  \brief Destructor of the Text class
        */
        ~Text() = default;

        /*!
        *  \brief Getter of the Texture Id
        */
        unsigned int getTextureID() const
        {
            return TextureID;
        }

        /*!
        *  \brief Getter of the size of glyph
        */
        glm::ivec2 getSize() const
        {
            return Size;
        }

        /*!
        *  \brief Getter of the offset from baseline to left/top of glyph
        */
        glm::ivec2 getBearing() const
        {
            return Bearing;
        }

        /*!
        *  \brief Getter of the offset to advance to next glyph
        */
        unsigned int getAdvance() const
        {
            return Advance;
        }

        /*!
        *  \brief Loads the font
        *
        *  \param Characters All the characters of the font
        * 
        */
        void loadFont(std::map<char, Text> &Characters)
        {

            FT_Library ft;
            if (FT_Init_FreeType(&ft))
            {
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            }

            FT_Face face;
            if (FT_New_Face(ft, "../Bubble_Run/assets/fonts/Findet Nemo.ttf", 0, &face))
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

     /*!
     *  \brief Displays the text
     *
     *  \param id : The program object to be queried
     *  \param Characters : a map of all the characters of the font
     *  \param text : the text that needs to be displayed
     *  \param x : the position of the text along the X axis
     *  \param y : the position of the text along the Y axis
     *  \param scale : defines the size of the displayed text
     *  \param color : defines the color of the displayed text
     * 
     */
        void RenderText(GLuint &id, std::map<char, Text> &Characters, std::string text, float x, float y, float scale, glm::vec3 color)
        {
            // activate corresponding render state
            glUniform3f(glGetUniformLocation(id, "textColor"), color.x, color.y, color.z);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(m_vao);

            // iterate through all characters
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++)
            {
                Text ch = Characters[*c];

                float xpos = x + ch.getBearing().x * scale;
                float ypos = y - (ch.getSize().y - ch.getBearing().y) * scale;

                float w = ch.getSize().x * scale;
                float h = ch.getSize().y * scale;
                // update m_vbo for each character
                float vertices[6][4] = {
                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos, ypos, 0.0f, 1.0f},
                    {xpos + w, ypos, 1.0f, 1.0f},

                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos + w, ypos, 1.0f, 1.0f},
                    {xpos + w, ypos + h, 1.0f, 0.0f}};
                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.getTextureID());
                // update content of m_vbo memory
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
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


        /*!
        *  \brief Render the text of the Score Menu
        *
        *  \param TextProgram : the corresponding ShaderManager
        *  \param Characters : a map of all the characters of the font
        *  \param scorejson : the saved scores that we want to display
        */
        void renderScoreText(rendering::ShaderManager &TextProgram, std::map<char, rendering::Text> &Characters, Score &scorejson)
        {
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            int first = scorejson.getArray()["score"][0];
            int second = scorejson.getArray()["score"][1];
            int third = scorejson.getArray()["score"][2];
            RenderText(id, Characters, "Best scores :", 300.0f, 400.0f, 0.6f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "First    " + std::to_string(first), 320.0f, 300.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f));
            RenderText(id, Characters, "Second   " + std::to_string(second), 320.0f, 250.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f));
            RenderText(id, Characters, "Third    " + std::to_string(third), 320.0f, 200.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f));
            RenderText(id, Characters, "Back", 690.0f, 50.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f));

            glDisable(GL_BLEND);
        }

        /*!
        *  \brief Render the text of the Main Menu
        *
        *  \param TextProgram : the corresponding ShaderManager
        *  \param Characters : a map of all the characters of the font
        */
        void renderMenuText(rendering::ShaderManager &TextProgram, std::map<char, rendering::Text> &Characters)
        {
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            RenderText(id, Characters, "... BUBBLE RUN ...", 270.0f, 400.0f, 0.8f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "play :", 365.0f, 290.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "score :", 360.0f, 215.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f));
            glDisable(GL_BLEND);
        }


        /*!
        *  \brief Render the text of the "Play Again" Menu
        *
        *  \param TextProgram : the corresponding ShaderManager
        *  \param Characters : a map of all the characters of the font
        *  \param score : the latest score
        */
        void renderPlayAgainText(rendering::ShaderManager &TextProgram, std::map<char, rendering::Text> &Characters, int &score)
        {
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            TextProgram.use();
            GLuint id = TextProgram.getId();
            RenderText(id, Characters, "... BUBBLE RUN ...", 270.0f, 400.0f, 0.8f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "play again :", 325.0f, 290.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "score :", 360.0f, 215.0f, 0.5f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "your score : " + std::to_string(score), 300.0f, 350.0f, 0.4f, glm::vec3(0.f, 0.04f, 0.39f));
            glDisable(GL_BLEND);
        }

        /*!
        *  \brief Render the text of the Game Window
        *
        *  \param TextProgram : the corresponding ShaderManager
        *  \param Characters : a map of all the characters of the font
        *  \param scorejson : the score of the current gaming session
        */
        void renderGameText(rendering::ShaderManager &TextProgram, std::map<char, rendering::Text> &Characters, int &score)
        {
            TextProgram.use();
            GLuint id = TextProgram.getId();
            std::string scorestring = std::to_string(score);
            RenderText(id, Characters, "BUBBLE RUN", 25.0f, 25.0f, 1.0f, glm::vec3(0.87f, 0.325f, 0.03f));
            RenderText(id, Characters, "Score : " + scorestring, 650.0f, 570.0f, 0.5f, glm::vec3(0.f, 0.04f, 0.39f));
        }

        /*!
        *  \brief Displays the text
        */
        void display()
        {
            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glEnable(GL_DEPTH_TEST);
        }
    };

}
#endif