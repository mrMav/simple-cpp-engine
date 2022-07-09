#pragma once

#include "OpenGL/Texture2D.h"
#include "OpenGL/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Engine
{
	using namespace glm;

	struct SpritebatchItem
	{
		VertexPositionColorTexture vertexTL;
		VertexPositionColorTexture vertexTR;
		VertexPositionColorTexture vertexBL;
		VertexPositionColorTexture vertexBR;

		Texture2D* texture = nullptr;

		void Set(uint32_t x, uint32_t y, uint16_t depth = 0)
		{
			vertexTL.Position = vec3(x, y, depth); // base depth of 0
			vertexTL.Color = vec3(1);          // white
			vertexTL.Texture = vec2(0, 0);

			vertexTR.Position = vec3(x + texture->GetWidth(), y, depth);
			vertexTR.Color = vec3(1);
			vertexTR.Texture = vec2(1, 0);

			vertexBL.Position = vec3(x, y + texture->GetHeight(), depth);
			vertexBL.Color = vec3(1);
			vertexBL.Texture = vec2(0, 1);

			vertexBR.Position = vec3(x + texture->GetWidth(), y + texture->GetHeight(), depth);
			vertexBR.Color = vec3(1);
			vertexBR.Texture = vec2(1, 1);

		}

		void Set(uint32_t x, uint32_t y, float angle, uint16_t depth = 0)
		{

			Set(x, y, x, y, angle, depth);

			vec2 test = rotate(vec2(10, 0), radians(90.0f));

		}

		void Set(uint32_t x, uint32_t y, float originX, float originY, float angle, uint16_t depth = 0)
		{
			
			vec2 origin = OriginToWorld(x, y, originX, originY);

			vertexTL.Position = vec3(RotateVertice(vec2(x, y), angle, origin), depth);
			vertexTL.Color = vec3(1);
			vertexTL.Texture = vec2(0, 0);

			vertexTR.Position = vec3(RotateVertice(vec2(x + texture->GetWidth(), y), angle, origin), depth);
			vertexTR.Color = vec3(1);
			vertexTR.Texture = vec2(1, 0);

			vertexBL.Position = vec3(RotateVertice(vec2(x, y + texture->GetHeight()), angle, origin), depth);
			vertexBL.Color = vec3(1);
			vertexBL.Texture = vec2(0, 1);

			vertexBR.Position = vec3(RotateVertice(vec2(x + texture->GetWidth(), y + texture->GetHeight()), angle, origin), depth);
			vertexBR.Color = vec3(1);
			vertexBR.Texture = vec2(1, 1);

		}

	private:

		vec2 RotateVertice(vec2& v, float angle, vec2& origin)
		{

			return rotate(v - origin, angle) + origin;

		}

		vec2 OriginToWorld(uint32_t x, uint32_t y, float oX, float oY)
		{
			vec2 result;

			result.x = ((x + texture->GetWidth()) - x) * oX + x;
			result.y = ((y + texture->GetHeight()) - y) * oY + y;

			return result;
		}

	};

}