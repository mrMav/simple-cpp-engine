#pragma once

#include <cinttypes>
#include <sstream>

namespace Engine
{
	/*class Rectangle
	{
	public:

		Rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

		uint32_t X, Y;

		uint32_t Width() { return m_Width; };
		void Width(uint32_t w);

		uint32_t

		uint32_t Height() { return m_Height; };
		void Height(uint32_t h);


	private:

		uint32_t m_Width, m_Height;		

	};*/

	template <typename T>
	class Rectangle
	{
	public:
		Rectangle() { };
		Rectangle(T x, T y, T w, T h)
			: X(x), Y(y)
		{
			Width(w);
			Height(h);
		};

		T X, Y;

		T Width() { return m_Width; };
		void Width(T w) { m_Width = w; m_HalfWidth = w / static_cast<T>(2); };

		T Height() { return m_Height; };
		void Height(T h) { m_Height = h; m_HalfHeight = h / static_cast<T>(2); };

		T HalfWidth() { return m_HalfWidth; };
		T HalfHeight() { return m_HalfHeight; };

	private:

		T m_Width, m_Height;
		T m_HalfWidth, m_HalfHeight;

	};

}