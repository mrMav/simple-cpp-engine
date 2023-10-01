
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image/stb_image.h>

#include <glad/glad.h>
#include <Internal.h>

#include "Texture2D.h"

namespace Engine
{

	Texture2D::Texture2D()
	{
		glGenTextures(1, &m_Texture);
	}

	Texture2D::Texture2D(int width, int height, TextureParams params)
		: Texture2D()
	{
		
		m_Params = params;
		m_Width = width;
		m_Height = height;

		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);


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

	Texture2D::Texture2D(const char* filename, TextureParams params)
		: Texture2D(0, 0, params)
	{
		LoadFromFile(filename);
	}

	void Texture2D::LoadFromFile(const char* filename)
	{

		//stbi_set_flip_vertically_on_load(true);
		// no need to invert
		// we will use top left for uv(0,0)

		unsigned char* data = stbi_load(filename, &m_Width, &m_Height, &m_Channels, 0);

		if (data)
		{

			GLuint format = m_Channels == 4 ? GL_RGBA : GL_RGB;
			
			Bind();
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);

		}
		else
		{

			_ENGINE_LOG("TEXTURE2D", std::string("Error loading file data into texture! ") + std::string(filename))

		}

		stbi_image_free(data);

	}

}