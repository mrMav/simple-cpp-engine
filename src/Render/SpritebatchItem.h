#pragma once

#include "OpenGL/Texture2D.h"
#include "OpenGL/VertexArray.h"
#include "Utils/Rectangle.h"

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

		void Set(int32_t x, int32_t y, int16_t depth = 0)
		{
			vertexTL.Position = vec3(x, y, depth); // base depth of 0
			vertexTL.Color = vec3(1);              // white
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

		void Set(int32_t x, int32_t y, float angle, int16_t depth = 0)
		{

			Set(x, y, x, y, angle, depth);

			vec2 test = rotate(vec2(10, 0), radians(90.0f));

		}

		void Set(int32_t x, int32_t y, float originX, float originY, float angle, int16_t depth = 0)
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

		void Set(int32_t x, int32_t y, Rectangle<int> clipRect, int16_t depth = 0)
		{

			glm::vec2 textureTL = GetTextureCoord(texture, clipRect.X, clipRect.Y);
			glm::vec2 textureBR = GetTextureCoord(texture, clipRect.X + clipRect.Width(), clipRect.Y + clipRect.Height());

			vertexTL.Position = vec3(x, y, depth);
			vertexTL.Color = vec3(1);
			vertexTL.Texture = textureTL;

			vertexTR.Position = vec3(x + clipRect.Width(), y, depth);
			vertexTR.Color = vec3(1);
			vertexTR.Texture = vec2(textureBR.x, textureTL.y);

			vertexBL.Position = vec3(x, y + clipRect.Height(), depth);
			vertexBL.Color = vec3(1);
			vertexBL.Texture = vec2(textureTL.x, textureBR.y);

			vertexBR.Position = vec3(x + clipRect.Width(), y + clipRect.Height(), depth);
			vertexBR.Color = vec3(1);
			vertexBR.Texture = textureBR;

		}

		void Set(int32_t x, int32_t y, Rectangle<int> clipRect, float originX, float originY, float angle, int16_t depth = 0)
		{

			glm::vec2 textureTL = GetTextureCoord(texture, clipRect.X, clipRect.Y);
			glm::vec2 textureBR = GetTextureCoord(texture, clipRect.X + clipRect.Width(), clipRect.Y + clipRect.Height());

			vec2 origin = OriginToWorld(x, y, originX, originY, clipRect);

			vertexTL.Position = vec3(RotateVertice(vec2(x, y), angle, origin), depth);
			vertexTL.Color = vec3(1);
			vertexTL.Texture = textureTL;

			vertexTR.Position = vec3(RotateVertice(vec2(x + clipRect.Width(), y), angle, origin), depth);
			vertexTR.Color = vec3(1);
			vertexTR.Texture = vec2(textureBR.x, textureTL.y);

			vertexBL.Position = vec3(RotateVertice(vec2(x, y + clipRect.Height()), angle, origin), depth);
			vertexBL.Color = vec3(1);
			vertexBL.Texture = vec2(textureTL.x, textureBR.y);

			vertexBR.Position = vec3(RotateVertice(vec2(x + clipRect.Width(), y + clipRect.Height()), angle, origin), depth);
			vertexBR.Color = vec3(1);
			vertexBR.Texture = textureBR;

		}

	private:

		/// <summary>
		/// Rotates a vertice 2d
		/// </summary>
		/// <param name="v"></param>
		/// <param name="angle"></param>
		/// <param name="origin"></param>
		/// <returns></returns>
		vec2 RotateVertice(vec2& v, float angle, vec2& origin)
		{

			return rotate(v - origin, angle) + origin;

		}

		/// <summary>
		/// Given a normalized origin of the sprite, return the equivalent position in world coordinates.
		/// </summary>
		/// <param name="x">The sprite X coordinate</param>
		/// <param name="y">The sprite Y coordinate</param>
		/// <param name="oX">The origin X value</param>
		/// <param name="oY">The origin Y value</param>
		/// <returns>A vec2 containing the calculated position in world coordinates.</returns>
		vec2 OriginToWorld(int32_t x, int32_t y, float oX, float oY)
		{
			vec2 result;

			result.x = ((x + texture->GetWidth()) - x) * oX + x;
			result.y = ((y + texture->GetHeight()) - y) * oY + y;

			return result;
		}

		/// <summary>
		/// Given a normalized origin of the sprite, return the equivalent position in world coordinates.
		/// </summary>
		/// <param name="x">The sprite X coordinate</param>
		/// <param name="y">The sprite Y coordinate</param>
		/// <param name="oX">The origin X value</param>
		/// <param name="oY">The origin Y value</param>
		/// <returns>A vec2 containing the calculated position in world coordinates.</returns>
		vec2 OriginToWorld(int32_t x, int32_t y, float oX, float oY, Rectangle<int> &clipRect)
		{
			vec2 result;

			result.x = ((x + clipRect.Width()) - x) * oX + x;
			result.y = ((y + clipRect.Height()) - y) * oY + y;

			return result;
		}

		/// <summary>
		/// Calculates normalized texture coordinates
		/// </summary>
		/// <param name="t"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns></returns>
		glm::vec2 GetTextureCoord(Texture2D* t, int x, int y)
		{
			return glm::vec2(x / static_cast<float>(t->GetWidth()), y / static_cast<float>(t->GetHeight()));
		}

	};

}