#include "TileSet.h"

namespace Engine
{
    TileSet::TileSet(Ref<Texture2D> ptexture, uint32_t pColsCount, uint32_t pRowsCount, uint32_t pTileHeight, uint32_t ptileWidth, uint32_t pmargin, uint32_t pspacing)
        : m_Texture(ptexture), m_ColumnsCount(pColsCount), m_RowsCount(pRowsCount), m_TileHeight(pTileHeight), m_TileWidth(ptileWidth), m_Margin(pmargin), m_Spacing(pspacing)
        {

        }

    Rectangle<int> TileSet::GetTileRect(uint32_t tileid) const
    {
        Rectangle<int> rect;

        rect.X = tileid % m_ColumnsCount * (m_TileWidth  + m_Spacing) + m_Margin;
        rect.Y = tileid / m_ColumnsCount * (m_TileHeight + m_Spacing) + m_Margin;
        rect.Width(m_TileWidth);
        rect.Height(m_TileHeight);

        return rect;
    }

    void TileSet::DrawTile(Ref<Spritebatch> batcher, glm::vec2 position, uint32_t tileid) const
    {
        batcher->Draw(m_Texture.get(), position.x, position.y, GetTileRect(tileid));
    }
}