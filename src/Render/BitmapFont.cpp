#include "BitmapFont.h"
#include "Internal.h"

namespace Engine
{

    BitmapFont::BitmapFont(const char* filename, int charWidth, int charHeight)
        : m_charWidth(charWidth), m_charHeight(charHeight)
    {
        m_fontData = new Texture2D(filename, {});

        // calculate maximum index possible
        m_nCols = m_fontData->GetWidth()  / charWidth;
        m_nRows = m_fontData->GetHeight() / charHeight;

        m_maxIndex = (m_nCols * m_nRows) - 1;

    }

    CharData BitmapFont::GetCharData(char c)
    {

        _ENGINE_FAIL_WITH_MSG(c > m_maxIndex, "BitmapFont can't print this character!\n")

        CharData d;

        d.x = c % m_nCols * m_charWidth;
        d.y = c / m_nCols * m_charHeight;
        d.w = m_charWidth;
        d.h = m_charHeight;

        return d;
    }

}