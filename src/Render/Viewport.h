#pragma once 

#include <glad/glad.h>

namespace Engine
{
	class Viewport
	{

	public:

		Viewport() { };

		Viewport(uint32_t w, uint32_t h) : m_Width(w), m_Height(h)
		{
			m_HalfWidth  = m_Width / 2.0f;
			m_HalfHeight = m_Height / 2.0f;
		};
		~Viewport() { };

		uint32_t Width() const { return m_Width; }
		uint32_t Height() const { return m_Height; }
		float HalfWidth() const { return m_HalfWidth; }
		float HalfHeight() const { return m_HalfHeight; }

		void SetWidth(uint32_t w) { m_Width = w; m_HalfWidth = m_Width / 2.0f; }
		void SetHeight(uint32_t h) { m_Height = h; m_HalfHeight = m_Height / 2.0f; }

		void Set() const { glViewport(0, 0, m_Width, m_Height); }

		float AspectRatio() { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

	private:

		uint32_t m_Width;

		uint32_t m_Height;

		float m_HalfWidth;

		float m_HalfHeight;

	};

}