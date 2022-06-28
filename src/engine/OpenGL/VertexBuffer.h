#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <vector>


namespace Engine
{

	class VertexBuffer
	{
	public:

		VertexBuffer(const void* data, const size_t dataSize)
			: m_Data(data), m_DataSize(dataSize)
		{
			glGenBuffers(1, &m_Handle);
			Bind();
			SetData(m_Data, m_DataSize);

		}
		~VertexBuffer() {};

		void Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void SetData(const void* data, const size_t size) const
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		void Delete()
		{
			glDeleteBuffers(1, &m_Handle);
		}

	private:

		GLuint m_Handle;

		const void* m_Data;

		size_t m_DataSize;

	};

}