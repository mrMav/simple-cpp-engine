#pragma once

#include <iostream>
#include <vector>
#include <string>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image/stb_image.h>

#include <glad/glad.h>

#include <Internal.h>
#include <Engine.h>

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

	class Texture2D {

	public:

		Texture2D(const char* filename, TextureParams params)
			: m_Params(params)
		{

			stbi_set_flip_vertically_on_load(true);

			unsigned char* data = stbi_load(filename, &m_Width, &m_Height, &m_Channels, 0);

			if (data)
			{

				//glActiveTexture(GL_TEXTURE0);

				glGenTextures(1, &m_Texture);
				glBindTexture(GL_TEXTURE_2D, m_Texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, m_Channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
				
				if (m_Params.GenMipmaps)
				{
					glGenerateMipmap(GL_TEXTURE_2D);
					
					if (m_Params.FilteringMin > GL_LINEAR_MIPMAP_LINEAR || m_Params.FilteringMin < GL_NEAREST_MIPMAP_NEAREST)
					{
						_ENGINE_LOG("TEXTURE", "Mipmap generation is turned on, but supplied MIN_FILTER does not use MIPMAPS.")
					}

				}

				SetParameteri(GL_TEXTURE_WRAP_S, m_Params.WrappingS);
				SetParameteri(GL_TEXTURE_WRAP_T, m_Params.WrappingT);
				SetParameteri(GL_TEXTURE_MIN_FILTER, m_Params.FilteringMin);
				SetParameteri(GL_TEXTURE_MAG_FILTER, m_Params.FilteringMax);

			}
			else
			{

				_ENGINE_LOG("TEXTURE2D", std::string("Error loading texture with filename: ") + std::string(filename))

			}

			stbi_image_free(data);

		};

		void Bind()
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
		};

		void SetParameteri(GLenum pname, int pvalue)
		{
			glTexParameteri(GL_TEXTURE_2D, pname, pvalue);
		};

	private:

		GLuint m_Texture;

		int m_Width, m_Height, m_Channels;

		TextureParams m_Params;

	};

}