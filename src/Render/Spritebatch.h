#pragma once

#include "OpenGL/Texture2D.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"

#include "Camera2D.h"
#include "SpritebatchItem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MAX_BATCH_ITEMS 512

namespace Engine
{

	struct BatchStats
	{
		uint32_t ItemCount;
		uint32_t TotalVertices;
		uint32_t TotalTriangles;
		uint32_t Flushs;

		void Reset()
		{
			ItemCount = 0;
			TotalVertices = 0;
			TotalTriangles = 0;
			Flushs = 0;
		}
	};

	class Spritebatch
	{
	public:

		Spritebatch();

		~Spritebatch()
		{
			delete[] m_Vertices;
			delete[] m_Indices;

			m_VertexArray->Delete();
		};

		void Begin(Shader* shader, Camera2D* camera, uint16_t depth);

		void End();

		void Draw(Texture2D* texture, uint32_t x, uint32_t y);
		void Draw(Texture2D* texture, uint32_t x, uint32_t y, float angle, float originX = 0.5f, float originY = 0.5f);

		const BatchStats& GetStats() const { return m_Stats;  }

	private:

		void Flush();
		void FlushIfNeeded();
		void CreateIndices();
		void Reset();
		void DrawBatch(Texture2D* texture);

		Shader* m_Shader = nullptr;
		Camera2D* m_Camera = nullptr;

		VertexArray* m_VertexArray = nullptr;

		std::vector<SpritebatchItem> m_BatchItems;

		VertexPositionColorTexture* m_Vertices = nullptr;
		uint16_t* m_Indices = nullptr;
		VertexPositionColorTexture* m_VerticesPtr = nullptr;
		uint16_t* m_IndicesPtr = nullptr;

		uint32_t m_BatchItemIndex = 0;

		BatchStats m_Stats;

		bool m_BeginCalled = false;



	};

}