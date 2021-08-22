/*
    This is a modified version of the SpriteFont class from the
    Seed Of Andromeda source code.
    Use it for any of your projects, commercial or otherwise,
    free of charge, but do not remove this disclaimer.
    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
    ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
    EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
    RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
    ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.
    November 28 2014
    Original Author: Cristian Zaloj
    Modified By: Benjamin Arnold
*/

#pragma once

#ifndef Text_h__
#define Text_h__

#include <map>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <SDLttf2/SDL_ttf.h>
#include <SDL/SDL.h>

#include <engine/Entity.h>
#include <engine/Module.h>
#include <rendering/ShaderProgram.h>
#include <data/Vertex.h>

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

namespace ShyEngine {

    class GLTexture;
    class SpriteBatch;

    struct CharGlyph {
    public:
        char character;
        glm::vec4 uvRect;
        glm::vec2 size;
    };

    typedef struct glyphdata {
        int minX;
        int maxX;
        int minY;
        int maxY;
        int advance;
        unsigned char glyph;
    }GlyphData;

    /// For text justification
    enum class Justification {
        LEFT, MIDDLE, RIGHT
    };

    class Text : public Module 
    {
        private:
            
            TTF_Font* m_currFont;
            CharGlyph* m_glyphs;
            ShaderProgram m_shader;

            int m_regStart, m_nCharacters;
            int m_fontHeight;

            unsigned int m_texID;

            std::vector<int>* createRows(GlyphData* rects, int rectsLength, int r, int padding, int& w);
            void init(const std::string& font, int size, unsigned int startChar, unsigned int endChar);

        public:
            Text(Entity* entity, const std::string& font, int size, unsigned char cs, unsigned char ce);
            Text(Entity* entity, const std::string& font, ShaderProgram shader, int size) :
                Text(entity, font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {
            }
            Text(Entity* entity, const std::string& font, const std::string& vertShader, const std::string& fragShader, int size) :
                Text(entity, font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {
            }
            /// Destroys the font resources
            void dispose();

            int getFontHeight() const {
                return m_fontHeight;
            }

            /// Measures the dimensions of the text
            glm::vec2 measure(const char* s);

            /// Draws using a spritebatch
            std::vector<CharGlyph> draw(SpriteBatch& batch, const char* s, glm::vec2 position, glm::vec2 scaling,
                float depth, ColorRGBA8 tint, Justification just = Justification::LEFT);
    };

}

#endif // SpriteFont_h__