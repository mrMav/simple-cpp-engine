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
				
				m_Texture = new Texture2D({});
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

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
		{
			delete m_Texture;
		};

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

		Texture2D* GetTexture() { return m_Texture; }

		GLuint GetHandle()
		{

			if (m_IsSample)
			{
				_ENGINE_LOG("asd", m_Texture->GetHandle())
				return m_Texture->GetHandle();
			}

			return m_Handle;
		}

	private:

		GLuint m_Handle;

		Texture2D* m_Texture = nullptr;

		bool m_IsSample;

		int m_Width, m_Height;

	};

}