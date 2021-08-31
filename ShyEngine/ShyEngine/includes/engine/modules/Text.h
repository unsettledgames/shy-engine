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

#include <map>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <SDLttf2/SDL_ttf.h>
#include <SDL/SDL.h>

#include <engine/modules/Sprite.h>
#include <engine/Entity.h>
#include <engine/Module.h>
#include <rendering/ShaderProgram.h>
#include <data/Vertex.h>
#include <data/Glyph.h>

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
        friend bool operator==(const Text& s1, const Text& s2);

        private:
            
            TTF_Font* m_currFont;
            CharGlyph* m_glyphs;
            ShaderProgram* m_shader;

            std::string m_text;
            ColorRGBA8 m_color;
            Justification m_justification;

            float m_depth;
            int m_regStart, m_nCharacters;
            int m_fontHeight;

            unsigned int m_texID;

            std::vector<int>* createRows(GlyphData* rects, int rectsLength, int r, int padding, int& w);
            void init(const std::string& font, int size, unsigned int startChar, unsigned int endChar);
            Text(Entity* entity, const std::string& font, int size, unsigned char cs, unsigned char ce);

        public:
            Text(Entity* entity, const std::string& font, ShaderProgram* shader, ColorRGBA8 color, int size, float depth,
                const std::string& text, Justification = Justification::LEFT);

            void setText(std::string& text) { m_text = text; }
            std::string getText() { return m_text; }

            /// Destroys the font resources
            void dispose();

            int getFontHeight() const { return m_fontHeight; }
            float getDepth() const { return m_depth; }
            GLuint getTextureId() const { return m_texID; }

            /// Measures the dimensions of the text
            glm::vec2 measure(const std::string& s);

            /// Draws using a spritebatch
            std::vector<Glyph> getGlyphs();
    };

}