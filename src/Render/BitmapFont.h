#pragma once

#include "OpenGL/Texture2D.h"
#include "glm/glm.hpp"

namespace Engine
{

    struct CharData
    {
        int x, y, w, h;
    };


    // Generates font data
    class BitmapFont
    {

        public:
        BitmapFont(const char* filename, int charWidth, int charHeight);
        ~BitmapFont()
        {
            // TODO: check if this is correct. We might need opengl context for this
            delete m_fontData;
        }

        Texture2D* GetTexture() { return m_fontData; }
        CharData GetCharData(char c);
        glm::vec2 GetStringSize(std::string str) const;

        int CharWidth() const { return m_charWidth; };
        int CharHeight() const { return m_charHeight; };

        private:
        
        Texture2D* m_fontData;

        int m_charWidth;
        int m_charHeight;

        int m_nCols;
        int m_nRows;

        char m_maxIndex;

    };

}


