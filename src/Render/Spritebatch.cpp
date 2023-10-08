
#include <glad/glad.h>
#include "Internal.h"
#include "Spritebatch.h"

namespace Engine
{
	Spritebatch::Spritebatch()
		: m_BatchItems(MAX_BATCH_ITEMS)
	{
		m_VertexArray = new VertexArray(&VertexPositionColorTexture::Attributes);

		m_Vertices = new VertexPositionColorTexture[MAX_BATCH_ITEMS * 4];
		m_Indices = new uint16_t[MAX_BATCH_ITEMS * 6];

		CreateIndices();
	}

	void Spritebatch::CreateIndices()
	{
		m_IndicesPtr = m_Indices;

		uint32_t offset = 0;
		for (int i = 0; i < MAX_BATCH_ITEMS; i++, m_IndicesPtr += 6, offset += 6)
		{
			*(m_IndicesPtr + 0) = (i * 4 + 0);
			*(m_IndicesPtr + 1) = (i * 4 + 1);
			*(m_IndicesPtr + 2) = (i * 4 + 3);
			*(m_IndicesPtr + 3) = (i * 4 + 1);
			*(m_IndicesPtr + 4) = (i * 4 + 2);
			*(m_IndicesPtr + 5) = (i * 4 + 3);			
		}

		m_IndicesPtr = m_Indices;
	}

	void Spritebatch::Begin(Shader* shader, Camera2D* camera, glm::vec4 tint, int16_t depth, bool customView)
	{
		_ENGINE_FAIL_WITH_MSG(!m_BeginCalled, "Spritebatch.Begin() was called, but Spritebatch.End() was never called!")

		Reset();
		m_Stats.Reset();

		m_Shader = shader;
		m_Camera = camera;
		m_Tint = tint;
		m_Depth = depth;
		m_DrawCustomView = customView;

		m_BeginCalled = true;

	}

	void Spritebatch::Reset()
	{
		// reset data
		m_BatchItemIndex = 0;
		m_VerticesPtr = m_Vertices;
		m_IndicesPtr = m_Indices;

		m_Tint = glm::vec4(1);
		m_Depth = 0;
		m_DrawCustomView = false;
	}

	void Spritebatch::End()
	{
		_ENGINE_FAIL_WITH_MSG(m_BeginCalled, "Spritebatch.Begin() was not called!")

		Flush();

		m_Shader = nullptr;
		m_Camera = nullptr;
		m_BeginCalled = false;

	}

	void Spritebatch::Draw(Texture2D* texture, float x, float y)
	{

		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y);
		item->Depth = m_Depth;

		m_Stats.ItemCount++;

	}

	void Spritebatch::Draw(Texture2D* texture, float x, float y, float angle, float originX, float originY)
	{

		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y, originX, originY, angle);

		m_Stats.ItemCount++;

	}


	void Spritebatch::Draw(Texture2D* texture, float x, float y, Rectangle<int> clipRect)
	{
		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y, clipRect);

		m_Stats.ItemCount++;

	}

	void Spritebatch::Draw(Texture2D* texture, float x, float y, Rectangle<int> clipRect, float angle, float originX, float originY)
	{
		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y, clipRect, originX, originY, angle);

		m_Stats.ItemCount++;

	}

	void Spritebatch::DrawString(BitmapFont* bitmapfont, float x, float y, const char* text)
	{
		int count = 0;
		float add_y = 0;
		float reset_x = 0;
		char c = text[count];


		while(c != '\0')
		{
			if(c == '\n')
			{
				add_y += bitmapfont->CharHeight() + 2;
				reset_x = 0;
				c = text[++count];
				continue;
			}

			CharData d = bitmapfont->GetCharData(c);
			Rectangle<int> rect = { d.x, d.y, d.w, d.h };

			Draw(bitmapfont->GetTexture(), x + reset_x * d.w, y + add_y, rect);
			
			reset_x++;
			c = text[++count];

		}
	}

	void Spritebatch::FlushIfNeeded()
	{

		if (m_BatchItemIndex + 1 == MAX_BATCH_ITEMS)
		{
			Flush();
			Reset();
		}
	}

	void Spritebatch::Flush()
	{
		//_ENGINE_PASS_OR_RETURN_MSG(m_BatchItemIndex > 0, "SpriteBatch", "No items to flush.")
		_ENGINE_PASS_OR_RETURN(m_BatchItemIndex > 0)
		

		m_Stats.Flushs++;

		Texture2D* currentTexture = m_BatchItems[0].texture;

		for (int i = 0; i < m_BatchItemIndex; i++, m_VerticesPtr += 4, m_IndicesPtr += 6)
		{

			if (m_BatchItems[i].texture != currentTexture)
			{
				DrawBatch(currentTexture);
				
				//m_BatchItems[i].texture = currentTexture;
				currentTexture = m_BatchItems[i].texture;


			}

			*(m_VerticesPtr + 0) = m_BatchItems[i].vertexTL;
			*(m_VerticesPtr + 1) = m_BatchItems[i].vertexTR;
			*(m_VerticesPtr + 2) = m_BatchItems[i].vertexBR;
			*(m_VerticesPtr + 3) = m_BatchItems[i].vertexBL;

			m_Stats.TotalVertices += 4;
			m_Stats.TotalTriangles += 2;

		}

		DrawBatch(currentTexture);

	}

	void Spritebatch::DrawBatch(Texture2D* texture)
	{
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		m_Shader->use();
		m_Shader->setMat4("uModel", glm::mat4(1));
		if(m_DrawCustomView)
			m_Shader->setMat4("uView", m_CustomView);
		else
			m_Shader->setMat4("uView", m_Camera->GetViewTransform());
		m_Shader->setMat4("uProjection", m_Camera->GetProjectionTransform());
		m_Shader->setVec4("uColor", m_Tint);

		// calculate how many vertices we are drawing
		uint32_t vertCount = m_VerticesPtr - m_Vertices;
		uint32_t indicesCount = m_IndicesPtr - m_Indices;

		assert(vertCount > 3);
		assert(indicesCount > 5);

		m_VertexArray->SetVertices(m_Vertices, vertCount * sizeof(VertexPositionColorTexture));
		m_VertexArray->SetIndices(m_Indices, indicesCount);
		m_VertexArray->DrawElements();

		m_VerticesPtr = m_Vertices;
		m_IndicesPtr = m_Indices;
	}

}
