
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

	void Spritebatch::Begin(Shader* shader, Camera2D* camera, uint16_t depth = 0)
	{
		_ENGINE_FAIL_WITH_MSG(!m_BeginCalled, "Spritebatch.Begin() was called, but Spritebatch.End() was never called!")

		m_Shader = shader;
		m_Camera = camera;

		Reset();
		m_Stats.Reset();

		m_BeginCalled = true;

	}

	void Spritebatch::Reset()
	{
		// reset data
		m_BatchItemIndex = 0;
		m_VerticesPtr = m_Vertices;
		m_IndicesPtr = m_Indices;
	}

	void Spritebatch::End()
	{
		_ENGINE_FAIL_WITH_MSG(m_BeginCalled, "Spritebatch.Begin() was not called!")

		Flush();

		m_Shader = nullptr;
		m_Camera = nullptr;
		m_BeginCalled = false;

	}

	void Spritebatch::Draw(Texture2D* texture, uint32_t x, uint32_t y)
	{

		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y);

		m_Stats.ItemCount++;

	}

	void Spritebatch::Draw(Texture2D* texture, uint32_t x, uint32_t y, float angle, float originX, float originY)
	{

		FlushIfNeeded();

		SpritebatchItem* item = &(m_BatchItems[m_BatchItemIndex++]);
		item->texture = texture;
		item->Set(x, y, originX, originY, angle);

		m_Stats.ItemCount++;

	}

	void Spritebatch::FlushIfNeeded()
	{

		if (m_BatchItemIndex + 1 == MAX_BATCH_ITEMS)
		{
			_ENGINE_LOG("SPRITEBATCH", "FLUSH NEEDED!")

			Flush();
			Reset();
		}
	}

	void Spritebatch::Flush()
	{

		m_Stats.Flushs++;

		Texture2D* currentTexture = m_BatchItems[0].texture;

		for (int i = 0; i < m_BatchItemIndex; i++, m_VerticesPtr += 4, m_IndicesPtr += 6)
		{
			*(m_VerticesPtr + 0) = m_BatchItems[i].vertexTL;
			*(m_VerticesPtr + 1) = m_BatchItems[i].vertexTR;
			*(m_VerticesPtr + 2) = m_BatchItems[i].vertexBR;
			*(m_VerticesPtr + 3) = m_BatchItems[i].vertexBL;

			m_Stats.TotalVertices += 4;
			m_Stats.TotalTriangles += 2;

			if (m_BatchItems[i].texture != currentTexture)
			{
				m_BatchItems[i].texture = currentTexture;

				DrawBatch(currentTexture);

			}

		}

		DrawBatch(currentTexture);

	}

	void Spritebatch::DrawBatch(Texture2D* texture)
	{
		glActiveTexture(GL_TEXTURE0);
		texture->Bind();

		m_Shader->use();
		m_Shader->setMat4("uModel", glm::mat4(1));
		m_Shader->setMat4("uView", m_Camera->GetViewTransform());
		m_Shader->setMat4("uProjection", m_Camera->GetProjectionViewTransform());

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
