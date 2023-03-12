#pragma once

#include <glad/glad.h>
#include <Internal.h>

#include "FrameBufferAttachment.h"

namespace Engine
{

	/// <summary>
	/// Creates a FrameBuffer to be used on offscreen rendering.
	/// Dont forget to call glViewport before drawing to the buffer.
	/// </summary>
	class FrameBuffer
	{

	public:

		FrameBuffer(int width, int height)
			: m_Width(width), m_Height(height)

		{
			glGenFramebuffers(1, &m_Handle);
			Bind();
			
			m_Color = FrameBufferAttachment(width, height, true);
			m_DepthStencil = FrameBufferAttachment(width, height, false);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color.GetHandle(), 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencil.GetHandle());

			
			_ENGINE_FAIL_WITH_MSG(CheckBufferStatus(), "Framebuffer not successfully created!");

			Unbind();

		}
		~FrameBuffer() {};

		void Bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
		};

		void BindTexture()
		{
			m_Color.Bind();
		}

		void Unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};

		void Delete()
		{
			glDeleteFramebuffers(1, &m_Handle);
		}

	private:

		GLuint m_Handle;

		FrameBufferAttachment m_Color;
		FrameBufferAttachment m_DepthStencil;

		int m_Width, m_Height;

		bool CheckBufferStatus()
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}

	};

}