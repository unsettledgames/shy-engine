#include "SpriteFont.h"

#include "SpriteBatch.h"


int closestPow2(int i) {
    i--;
    int pi = 1;
    while (i > 0) {
        i >>= 1;
        pi <<= 1;
    }
    return pi;
}

#define MAX_TEXTURE_RES 4096

namespace ShyEngine {

    SpriteFont::SpriteFont(const char* font, int size, unsigned char startChar, unsigned char endChar) 
    {
        // Initialize SDL_ttf
        if (!TTF_WasInit())
            TTF_Init();

        // Open the font
        TTF_Font* currFont = TTF_OpenFont(font, size);
        if (currFont == nullptr) 
        {
            fprintf(stderr, "Failed to open TTF font %s\n", font);
            throw 281;
        }
        
        // Setting start stats
        m_fontHeight = TTF_FontHeight(currFont);
        // Beginning character
        m_regStart = startChar;
        // Number of characters
        m_regLength = endChar - startChar + 1;
        // FEATURE: let the user choose padding between letters
        int padding = size / 8;

        /*
            First measure all the regions
        */
        GlyphData* glyphRects = new GlyphData[m_regLength];
        int i = 0, advance;
        for (unsigned char c = startChar; c <= endChar; c++) 
        {
            TTF_GlyphMetrics(currFont, c, &glyphRects[i].minX, &glyphRects[i].maxX, &glyphRects[i].minY, &glyphRects[i].maxY, &advance);
            i++;
        }

        // Find best partitioning of glyphs
        int rows = 1, width, height, bestWidth = 0, bestHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestRows = 0;
        std::vector<int>* bestPartition = nullptr;
        while (rows <= m_regLength) 
        {
            // to understand better
            height = rows * (padding + m_fontHeight) + padding;
            std::vector<int>* glyphRow = createRows(glyphRects, m_regLength, rows, padding, width);

            // Desire a power of 2 texture
            width = closestPow2(width);
            height = closestPow2(height);

            // A texture must be feasible
            if (width > MAX_TEXTURE_RES || height > MAX_TEXTURE_RES) 
            {
                rows++;
                delete[] glyphRow;
                continue;
            }

            // Check for minimal area
            if (area >= width * height) 
            {
                if (bestPartition) delete[] bestPartition;
                bestPartition = glyphRow;
                bestWidth = width;
                bestHeight = height;
                bestRows = rows;
                area = bestWidth * bestHeight;
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
            fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", font);
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

        // what the flying fuck Ben I love your tutorials but please add a fucking comment once
        // every 100 lines ffs
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
                SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(currFont, (unsigned char)(startChar + glyphIdx), foregroundColor);

                // Pre-multiplication occurs 
                /* ISSUE: uncomment this
                unsigned char* surfacePixels = (unsigned char*)glyphSurface->pixels;
                int nPixels = glyphSurface->w * glyphSurface->h * 4;
                for (int i = 0; i < nPixels; i += 4) 
                {
                    float a = surfacePixels[i + 3] / 255.0f;
                    surfacePixels[i] *= a;
                    surfacePixels[i + 1] = surfacePixels[i];
                    surfacePixels[i + 2] = surfacePixels[i];
                }*/

                // Save glyph image and update coordinates
                // BUG: probabilmente il problema è negli offset in questa chiamata
                glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, bestHeight - yOffset - glyphSurface->h, 
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
        m_glyphs = new CharGlyph[m_regLength + 1];
        for (i = 0; i < m_regLength; i++) 
        {
            m_glyphs[i].character = (unsigned char)(startChar + i);
            m_glyphs[i].size = glm::vec2(glyphRects[i].maxX, glyphRects[i].maxY);
            m_glyphs[i].uvRect = glm::vec4(
                (float)glyphRects[i].minX / (float)bestWidth,
                (float)glyphRects[i].minY / -(float)bestHeight,
                (float)glyphRects[i].maxX / (float)bestWidth,
                (float)glyphRects[i].maxY / -(float)bestHeight
            );
        }
        m_glyphs[m_regLength].character = ' ';
        m_glyphs[m_regLength].size = m_glyphs[0].size;
        m_glyphs[m_regLength].uvRect = glm::vec4(0, 0, (float)rs / (float)bestWidth, (float)rs / -(float)bestHeight);

        glBindTexture(GL_TEXTURE_2D, 0);
        delete[] glyphRects;
        delete[] bestPartition;
        TTF_CloseFont(currFont);
    }

    void SpriteFont::dispose() 
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

    // The problem is probably here
    std::vector<int>* SpriteFont::createRows(GlyphData* rects, int rectsLength, int nRows, 
        int padding, int& rowWidth) 
    {
        // Blank initialize
        // Vettore di vettori contenenti interi, questa roba è una matrice di interi alta nRows
        std::vector<int>* rowList = new std::vector<int>[nRows]();
        int* currWidths = new int[nRows];
        for (int i = 0; i < nRows; i++)
            currWidths[i] = padding;

        // Loop through all glyphs
        for (int i = 0; i < rectsLength; i++) 
        {
            // Find row for placement
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

    // SAFE returns the size of a string
    glm::vec2 SpriteFont::measure(const char* s) {
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
                if (gi < 0 || gi >= m_regLength)
                    gi = m_regLength;
                cw += m_glyphs[gi].size.x;
            }
        }
        if (size.x < cw)
            size.x = cw;
        return size;
    }

    /*
        SAFE
    */
    void SpriteFont::draw(SpriteBatch& batch, const char* s, glm::vec2 position, glm::vec2 scaling,
        float depth, ColorRGBA8 tint, Justification just /* = Justification::LEFT */) 
    {
        glm::vec2 textPos = position;
        // Apply justification
        if (just == Justification::MIDDLE)
            textPos.x -= measure(s).x * scaling.x / 2;
        else if (just == Justification::RIGHT)
            textPos.x -= measure(s).x * scaling.x;

        for (int strIndex = 0; s[strIndex] != 0; strIndex++) 
        {
            unsigned char c = s[strIndex];
            // Returning to start of the line, moving to new line
            if (c == '\n') 
            {
                textPos.y += m_fontHeight * scaling.y;
                textPos.x = position.x;
            }
            // Print the current clyph
            else 
            {
                // Get correct glyph
                int glyphIndex = c - m_regStart;
                if (glyphIndex < 0 || glyphIndex >= m_regLength)
                    glyphIndex = m_regLength;

                // Glyph starts from textpos, size is the size of the glyph with scaling applied to it
                glm::vec4 destRect(textPos, m_glyphs[glyphIndex].size * scaling);
                // Draw the glyph
                batch.draw(destRect, m_glyphs[glyphIndex].uvRect, m_texID, depth, tint);
                // Basically move the cursor
                textPos.x += m_glyphs[glyphIndex].size.x * scaling.x;
            }
        }
    }

}