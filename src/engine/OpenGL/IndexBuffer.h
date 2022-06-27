#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>


namespace Engine
{

	class IndexBuffer
	{

	public:

		IndexBuffer(const void* data, const size_t count)
			: m_Data(data), m_DataCount(count)
		{
			// class constructor
			// creates the handles for gl objects

			glGenBuffers(1, &m_Handle);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);

			// sends the data to gpu
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_DataCount * sizeof(uint16_t), data, GL_STATIC_DRAW);
		}
		~IndexBuffer() {};

		void Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
		};

		void Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		};

		void Delete()
		{
			glDeleteBuffers(1, &m_Handle);
		}

		size_t GetDataCount() const { return m_DataCount; };

	private:

		GLuint m_Handle;

		const void* m_Data;

		size_t m_DataCount;

	};

}