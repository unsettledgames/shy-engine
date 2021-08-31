#include <engine/modules/Text.h>
#include <iostream>

namespace ShyEngine 
{
    #define MAX_TEXTURE_RES 4096

    bool operator==(const Text& s1, const Text& s2)
    {
        return s1.m_id == s2.m_id;
    }

    int closestPow2(int i) {
        i--;
        int pi = 1;
        while (i > 0) {
            i >>= 1;
            pi <<= 1;
        }
        return pi;
    }

    Text::Text(Entity* entity, const std::string& font, int size, unsigned char startChar, unsigned char endChar) : 
        Module("Text", entity)
    {
        init(font, size, startChar, endChar);
    }

    Text::Text(Entity* entity, const std::string& font, ShaderProgram* shader, ColorRGBA8 color, int size, float depth,
        const std::string& text, Justification justification) :
        Text(entity, font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) 
    {
        m_depth = depth;
        m_text = text;
        m_shader = shader;
        m_color = color;
        m_justification = justification;
    }

    void Text::init(const std::string& font, int size, unsigned int startChar, unsigned int endChar)
    {
        // Initialize SDL_ttf
        if (!TTF_WasInit())
            TTF_Init();

        // Open the font
        m_currFont = TTF_OpenFont(font.c_str(), size);
        if (m_currFont == nullptr)
        {
            fprintf(stderr, "Failed to open TTF font %s\n", font.c_str());
            throw 281;
        }

        // Setting start stats
        m_fontHeight = TTF_FontHeight(m_currFont);
        // Beginning character
        m_regStart = startChar;
        // Number of characters
        m_nCharacters = endChar - startChar + 1;
        // FEATURE: let the user choose padding between letters
        int padding = size / 8;

        /*
            First measure all the regions
        */
        GlyphData* glyphRects = new GlyphData[m_nCharacters];
        int i = 0, advance;
        for (unsigned char c = startChar; c <= endChar; c++)
        {
            TTF_GlyphMetrics(m_currFont, c, &(glyphRects[i].minX), &(glyphRects[i].maxX), &(glyphRects[i].minY), &(glyphRects[i].maxY), &advance);
            glyphRects[i].glyph = c;
            i++;
        }

        // Find best partitioning of glyphs
        int rows = 1, bestRows = 0;
        int currWidth, currHeight;
        int bestWidth = 0, bestHeight = 0;
        int textureArea = MAX_TEXTURE_RES * MAX_TEXTURE_RES;
        std::vector<int>* bestPartition = nullptr;

        // OPTIMIZABLE: fix the packing algorithm (with the 04 font, it screws up at the 7th iteration
        while (rows <= 1)
        {
            // I have rows, each row has a height of m_fontHeight and I have to add padding to it
            currHeight = rows * (padding + m_fontHeight);
            std::vector<int>* glyphRow = createRows(glyphRects, m_nCharacters, rows, padding, currWidth);

            // Desire a power of 2 texture
            currWidth = closestPow2(currWidth);
            currHeight = closestPow2(currHeight);

            // A texture must be feasible
            if (currWidth > MAX_TEXTURE_RES || currHeight > MAX_TEXTURE_RES)
            {
                rows++;
                delete[] glyphRow;
                continue;
            }

            // Check for minimal area
            if (textureArea >= currWidth * currHeight)
            {
                if (bestPartition) delete[] bestPartition;
                bestPartition = glyphRow;
                bestWidth = currWidth;
                bestHeight = currHeight;
                bestRows = rows;
                textureArea = bestWidth * bestHeight;
                rows++;
            }
            else
            {
                delete[] glyphRow;
                break;
            }
        }

        // Can a bitmap font be made?
        if (!bestPartition)
        {
            fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", font.c_str());
            throw 282;
        }

        // Create the texture
        glGenTextures(1, &m_texID);
        glBindTexture(GL_TEXTURE_2D, m_texID);
        // For a last resource I could try setting the max width and height, I should look
        // in createRows to see their values
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestWidth, bestHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // Now draw all the glyphs
        SDL_Color foregroundColor = { 255, 255, 255, 255 };

        int yOffset = padding;
        // For each glyph row
        for (int rowIdx = 0; rowIdx < bestRows; rowIdx++)
        {
            int xOffset = padding;

            for (size_t colIdx = 0; colIdx < bestPartition[rowIdx].size(); colIdx++)
            {
                // Current glyph index
                int glyphIdx = bestPartition[rowIdx][colIdx];
                // Surface for the current glyph
                SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(m_currFont, (unsigned char)(startChar + glyphIdx), foregroundColor);

                // Pre-multiplication occurs 
                unsigned char* surfacePixels = (unsigned char*)glyphSurface->pixels;
                int nPixels = glyphSurface->w * glyphSurface->h * 4;
                for (int i = 0; i < nPixels; i += 4)
                {
                    float a = surfacePixels[i + 3] / 255.0f;
                    surfacePixels[i] *= a;
                    surfacePixels[i + 1] = surfacePixels[i];
                    surfacePixels[i + 2] = surfacePixels[i];
                }
                
                // BUG PROBABLY HERE
                // Save glyph image and update coordinates
                glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, bestHeight - yOffset / size - glyphSurface->h,
                    glyphSurface->w, glyphSurface->h, GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
                glyphRects[glyphIdx].minX = xOffset;
                glyphRects[glyphIdx].minY = yOffset;
                glyphRects[glyphIdx].maxX = glyphSurface->w;
                glyphRects[glyphIdx].maxY = glyphSurface->h;

                SDL_FreeSurface(glyphSurface);
                glyphSurface = nullptr;

                xOffset += glyphRects[glyphIdx].maxX + padding;
            }
            yOffset += m_fontHeight + padding;
        }

        // Draw the unsupported glyph <- why?
        int rs = padding - 1;

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Create spriteBatch glyphs
        m_glyphs = new CharGlyph[m_nCharacters + 1];
        for (i = 0; i < m_nCharacters; i++)
        {
            m_glyphs[i].character = (unsigned char)(startChar + i);
            m_glyphs[i].size = glm::vec2(glyphRects[i].maxX, glyphRects[i].maxY);
            m_glyphs[i].uvRect = glm::vec4(
                (float)glyphRects[i].minX / (float)bestWidth,
                (float)glyphRects[i].minY / (float)bestHeight,
                (float)glyphRects[i].maxX / (float)bestWidth,
                (float)glyphRects[i].maxY / (float)bestHeight
            );
        }
        m_glyphs[m_nCharacters].character = ' ';
        m_glyphs[m_nCharacters].size = m_glyphs[0].size;
        m_glyphs[m_nCharacters].uvRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / (float)bestHeight);

        glBindTexture(GL_TEXTURE_2D, 0);
        delete[] glyphRects;
        delete[] bestPartition;
    }

    void Text::dispose()
    {
        if (m_texID != 0) {
            glDeleteTextures(1, &m_texID);
            m_texID = 0;
        }
        if (m_glyphs) {
            delete[] m_glyphs;
            m_glyphs = nullptr;
        }
    }

    std::vector<int>* Text::createRows(GlyphData* rects, int rectsLength, int nRows,
        int padding, int& rowWidth) 
    {
        // Blank initialize
        // Vettore di vettori contenenti interi, questa roba è una matrice di interi alta nRows
        std::vector<int>* rowList = new std::vector<int>[nRows]();
        // Curr widths keeps track of the width of each row of glyphs
        int* currWidths = new int[nRows];
        for (int i = 0; i < nRows; i++)
            currWidths[i] = padding;

        // Loop through all glyphs
        for (int i = 0; i < rectsLength; i++) 
        {
            // Find row for placement: I put the character in the row that has less characters
            int rowIdx = 0;
            for (int j = 1; j < nRows; j++)
            {
                if (currWidths[j] < currWidths[rowIdx])
                    rowIdx = j;
            }

            // Add width to that row
            currWidths[rowIdx] += rects[i].maxX + padding;

            // Add glyph to the row list
            rowList[rowIdx].push_back(i);
        }

        // Find the max width
        rowWidth = 0;
        for (int i = 0; i < nRows; i++) 
        {
            if (currWidths[i] > rowWidth) 
                rowWidth = currWidths[i];
        }

        return rowList;
    }

    // returns the size of a string
    glm::vec2 Text::measure(const std::string& s) {
        glm::vec2 size(0, m_fontHeight);
        float cw = 0;
        for (int si = 0; s[si] != 0; si++) {
            unsigned char c = s[si];
            if (s[si] == '\n') {
                size.y += m_fontHeight;
                if (size.x < cw)
                    size.x = cw;
                cw = 0;
            }
            else {
                // Check for correct glyph
                int gi = c - m_regStart;
                if (gi < 0 || gi >= m_nCharacters)
                    gi = m_nCharacters;
                cw += m_glyphs[gi].size.x;
            }
        }
        if (size.x < cw)
            size.x = cw;
        return size;
    }

    std::vector<Glyph> Text::getGlyphs()
    {
        Texture currTexture;
        Glyph currGlyph;
        std::vector<Glyph> ret;
        Transform* transform = (Transform*)m_entity->getModule("Transform");

        glm::vec2 position = transform->getPos();
        glm::vec2 scaling = transform->getScale();

        currTexture.id = m_texID;

        glm::vec2 textPos = position;
        // Apply justification
        if (m_justification == Justification::MIDDLE)
            textPos.x -= measure(m_text).x * scaling.x / 2;
        else if (m_justification == Justification::RIGHT)
            textPos.x -= measure(m_text).x * scaling.x;

        for (int strIndex = 0; m_text[strIndex] != 0; strIndex++)
        {
            unsigned char currChar = m_text[strIndex];
            // Returning to start of the line, moving to new line
            if (currChar == '\n')
            {
                textPos.x = position.x;
                textPos.y -= m_fontHeight * scaling.y;
            }
            // Print the current clyph
            else
            {
                // Get correct glyph
                int glyphIndex = currChar - m_regStart;
                if (glyphIndex < 0 || glyphIndex >= m_nCharacters)
                    glyphIndex = m_nCharacters;
                CharGlyph charGlyph = m_glyphs[glyphIndex];

                // Creating a glyph for the current character
                currGlyph = Glyph(currTexture, m_shader, m_color, textPos,
                    glm::vec2(scaling.x * charGlyph.size.x, scaling.y * charGlyph.size.y), charGlyph.uvRect, m_depth);
                // Add the glyph
                ret.push_back(currGlyph);
                // Basically move the cursor
                textPos.x += charGlyph.size.x * scaling.x;
            }
        }

        return ret;
    }
}