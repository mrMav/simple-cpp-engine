#pragma once 

namespace Engine
{
	class Viewport
	{

	public:

		Viewport(uint32_t w, uint32_t h) : m_Width(w), m_Height(h) { };
		~Viewport() { };

		uint32_t Width() const { return m_Width; }
		uint32_t Height() const { return m_Height; }

		void SetWidth(uint32_t w) { m_Width = w; }
		void SetHeight(uint32_t h) { m_Height = h; }

		float AspectRatio() { return static_cast<float>(m_Width) / static_cast<float>(m_Height); }

	private:

		uint32_t m_Width;

		uint32_t m_Height;

	};

}