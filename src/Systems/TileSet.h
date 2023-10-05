#include "Internal.h"
#include "OpenGL/Texture2D.h"
#include "Render/Spritebatch.h"
#include "Utils/Rectangle.h"

namespace Engine
{
    
    class TileSet
    {
    private:
        Ref<Texture2D> m_Texture;
        uint32_t m_ColumnsCount, m_RowsCount, m_TileHeight, m_TileWidth, m_Margin, m_Spacing;

    public:
        TileSet(Ref<Texture2D> ptexture,
            uint32_t pColsCount,
            uint32_t pRowsCount,
            uint32_t pTileHeight,
            uint32_t ptileWidth,
            uint32_t pmargin = 0,
            uint32_t pspacing = 0);
        ~TileSet() {};

        Rectangle<int> GetTileRect(uint32_t tileid) const;

        void DrawTile(Ref<Spritebatch> batcher, glm::vec2 position, uint32_t tileid) const;
    };
    

} // namespace Engine
