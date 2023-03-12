#pragma once

#include <glad/glad.h>

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
				// generate a texture
				glGenTextures(1, &m_Handle);
				Bind();

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
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

		~FrameBufferAttachment() {};

		void Bind()
		{
			if (m_IsSample)
				glBindTexture(GL_TEXTURE_2D, m_Handle);
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

		GLuint GetHandle() { return m_Handle; }

	private:

		GLuint m_Handle;

		bool m_IsSample;

		int m_Width, m_Height;

	};

}