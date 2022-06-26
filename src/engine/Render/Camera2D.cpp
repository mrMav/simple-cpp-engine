
#include "Camera2D.h"

namespace Engine
{
	Camera2D::Camera2D(const Viewport& v)
		: m_Viewport(v)
	{
		m_Origin = glm::vec3(m_Viewport.Width() / 2.0f, m_Viewport.Height() / 2.0f, 0.0f);
		Position = glm::vec3(0.0f);
		Position.z = -1.0f;

		m_ProjectionTransform = glm::ortho<float>(0, m_Viewport.Width(), 0, m_Viewport.Height(), -100, 100);
		UpdateViewTransform();
		
	}

	void Camera2D::Update(float gameTime) //TODO: make delta time a struct with access to ellpased time, etc
	{
		UpdateViewTransform();
	}

	void Camera2D::UpdateViewTransform()
	{
		m_ViewTransform = glm::inverse(glm::translate(Position));
		m_ViewProjectionTransform = m_ProjectionTransform * m_ViewTransform;		
	}

}