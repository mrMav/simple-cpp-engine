#pragma once

#include "OpenGL/Texture2D.h"

namespace Engine
{

    struct CharData
    {
        uint16_t x, y, w, h;
    };


    // Generates font data
    class BitmapFont
    {

        public:
        BitmapFont(const char* filename, uint16_t charWidth, uint16_t charHeight);
        ~BitmapFont()
        {
            // TODO: check if this is correct. We might need opengl context for this
            delete m_fontData;
        }

        Texture2D* GetTexture() { return m_fontData; }
        CharData GetCharData(char c);

        private:
        
        Texture2D* m_fontData;

        uint16_t m_charWidth;
        uint16_t m_charHeight;

        uint16_t m_nCols;
        uint16_t m_nRows;

        char m_maxIndex;

    };

}


