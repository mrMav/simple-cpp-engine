
#include "Camera2D.h"

namespace Engine
{
	Camera2D::Camera2D(Viewport& v)
		: m_Viewport(v)
	{
		UpdateOrigin();
		Position = glm::vec3(0.0f);  // camera coords are in world coords, since the camera IS the world
		Position.z = -1.0f;

		Zoom = 1.0f;

		UpdateProjection();
		
	}

	void Camera2D::UpdateProjection()
	{
		m_ProjectionTransform = glm::ortho<float>(0, m_Viewport.Width(), m_Viewport.Height(), 0, -100, 100);
	}

	void Camera2D::UpdateOrigin()
	{
		m_Origin = glm::vec3(m_Viewport.Width() / 2.0f, m_Viewport.Height() / 2.0f, 0.0f);
	}

	void Camera2D::SetViewport(Viewport& v)
	{
		m_Viewport = v;
		UpdateOrigin();
		UpdateProjection();

	}


	void Camera2D::Update(float gameTime) //TODO: make delta time a struct with access to ellpased time, etc
	{
		// updates the view matrix		
		glm::mat4 position = glm::translate(glm::vec3(-Position.x, -Position.y, 0));
		glm::mat4 scale = glm::scale(glm::vec3(Zoom, Zoom, 1));

		glm::mat4 halfScreen = glm::translate(glm::vec3(m_Viewport.HalfWidth(), m_Viewport.HalfHeight(), 0));

		//m_ViewTransform = position * scale;// this works wonders

		// but I want to try and scale with reference point
		//m_ViewTransform = halfScreen * scale * glm::inverse(halfScreen) * position; // this scales towrds the center of the screen
		m_ViewTransform = halfScreen * scale * glm::inverse(halfScreen) * position * halfScreen; // this scales towrds the center of the screen
	}

	glm::vec2 Camera2D::ScreenToWorld(int x, int y)
	{
		return ScreenToWorld(glm::vec2(x, y));
	}

	glm::vec2 Camera2D::ScreenToWorld(const glm::vec2& pos)
	{
		return (glm::inverse(m_ViewTransform) * glm::vec4(pos, 0, 1));
	}

	glm::vec2 Camera2D::WorldToScreen(int x, int y)
	{
		return WorldToScreen(glm::vec2(x, y));
	}

	glm::vec2 Camera2D::WorldToScreen(const glm::vec2& pos)
	{
		return (m_ViewTransform * glm::vec4(pos, 0, 1));
	}

	glm::vec2 Camera2D::GetCameraDisplaySize() const
	{
		return glm::vec2(GetViewport().Width() / Zoom, GetViewport().Height() / Zoom);
	}

}