#pragma once

#include "OpenGL/Texture2D.h"

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

        private:
        
        Texture2D* m_fontData;

        int m_charWidth;
        int m_charHeight;

        int m_nCols;
        int m_nRows;

        char m_maxIndex;

    };

}


