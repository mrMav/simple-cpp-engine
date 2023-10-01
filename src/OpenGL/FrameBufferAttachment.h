#pragma once

#include <string>
#include <glad/glad.h>
#include <Internal.h>

#include "Texture2D.h"

namespace Engine
{

	class FrameBufferAttachment
	{
	public:

		FrameBufferAttachment() { };

		FrameBufferAttachment(int width, int height, bool isSample)
			: m_Width(width), m_Height(height), m_IsSample(isSample)
		{

			if (isSample)
			{
				
				m_Texture = std::make_shared<Texture2D>(width, height, TextureParams());
				_ENGINE_LOG("OPENGL", "Created frame buffer attachment of type texture.")
			}
			else
			{
				// generate renderbuffer
				glGenRenderbuffers(1, &m_Handle);
				Bind();

				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

				_ENGINE_LOG("OPENGL", "Created frame buffer attachment of type renderbuffer.")

			}

			Unbind();
		}

		~FrameBufferAttachment()
		{ };

		void Bind()
		{
			if (m_IsSample)
				m_Texture->Bind();
			else
				glBindRenderbuffer(GL_RENDERBUFFER, m_Handle);
		};

		void Unbind()
		{
			if (m_IsSample)
				glBindTexture(GL_TEXTURE_2D, 0);
			else
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
		};

		void Delete()
		{

		};

		Ref<Texture2D> GetTexture() { return m_Texture; }

		GLuint GetHandle()
		{

			if (m_IsSample)
			{
				return m_Texture->GetHandle();
			}

			return m_Handle;
		}

	private:

		GLuint m_Handle;

		Ref<Texture2D> m_Texture;

		bool m_IsSample;

		int m_Width, m_Height;

	};

}