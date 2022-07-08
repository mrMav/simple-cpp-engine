#pragma once

#include "OpenGL/Texture2D.h"
#include "OpenGL/VertexArray.h"

#include <glm/glm.hpp>

namespace Engine
{
	struct SpritebatchItem
	{
		VertexPositionColorTexture vertexTL;
		VertexPositionColorTexture vertexTR;
		VertexPositionColorTexture vertexBL;
		VertexPositionColorTexture vertexBR;

		Texture2D* texture = nullptr;

		void Set(uint32_t x, uint32_t y, uint16_t depth = 0)
		{
			vertexTL.Position = glm::vec3(x, y, depth); // base depth of 0
			vertexTL.Color = glm::vec3(1);          // white
			vertexTL.Texture = glm::vec2(0, 0);

			vertexTR.Position = glm::vec3(x + texture->GetWidth(), y, depth);
			vertexTR.Color = glm::vec3(1);
			vertexTR.Texture = glm::vec2(1, 0);

			vertexBL.Position = glm::vec3(x, y + texture->GetHeight(), depth);
			vertexBL.Color = glm::vec3(1);
			vertexBL.Texture = glm::vec2(0, 1);

			vertexBR.Position = glm::vec3(x + texture->GetWidth(), y + texture->GetHeight(), depth);
			vertexBR.Color = glm::vec3(1);
			vertexBR.Texture = glm::vec2(1, 1);

		}

	};

}