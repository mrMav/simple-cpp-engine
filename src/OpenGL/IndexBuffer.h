#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>


namespace Engine
{

	class IndexBuffer
	{

	public:

		IndexBuffer()
		{
			// class constructor
			// creates the handles for gl objects

			glGenBuffers(1, &m_Handle);
			Bind();

		}
		~IndexBuffer() {};

		void Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
		};

		void SetData(const void* data, const size_t count)
		{
			m_DataCount = count;

			// sends the data to gpu
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_DataCount * sizeof(uint16_t), data, GL_STATIC_DRAW);
		}

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