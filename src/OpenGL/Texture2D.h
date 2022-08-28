#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>

namespace Engine
{
	struct TextureParams
	{
		TextureParams(
			uint32_t wrap_s = GL_REPEAT,
			uint32_t wrap_t = GL_REPEAT,
			uint32_t filter_min = GL_NEAREST,
			uint32_t filter_max = GL_NEAREST,
			bool gen_mip = false)
			: WrappingS(wrap_s), WrappingT(wrap_t), FilteringMin(filter_min),
			FilteringMax(filter_max), GenMipmaps(gen_mip)
		{

		}

		uint32_t WrappingS;
		uint32_t WrappingT;
		uint32_t FilteringMin;
		uint32_t FilteringMax;
		bool GenMipmaps;
	};
	
	class Texture2D
	{

	public:

		Texture2D(const char* filename, TextureParams params);
		~Texture2D() { };

		void Bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
		};

		void SetParameteri(GLenum pname, int pvalue)
		{
			glTexParameteri(GL_TEXTURE_2D, pname, pvalue);
		};

		int GetWidth() { return m_Width; };
		int GetHeight() { return m_Height; };

	private:

		GLuint m_Texture;

		int m_Width, m_Height, m_Channels;

		TextureParams m_Params;

	};

}