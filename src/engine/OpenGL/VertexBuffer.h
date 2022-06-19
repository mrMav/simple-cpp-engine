#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"

class VertexBuffer
{
	public:

		VertexBuffer(const std::vector<VertexPositionNormalTexture>& data);  // later we can add support for other vertex types
		~VertexBuffer();

		void Bind();

		void Unbind();

		void Delete();

private:

	GLuint m_vbo;

	// will hold the data
	// we will decompose the received data to an interleaved array
	float* m_data;

	uint32_t m_dataCount;

};

