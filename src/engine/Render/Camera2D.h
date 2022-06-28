#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Viewport.h"

namespace Engine
{

	class Camera2D
	{
	public:

		glm::vec3 Position;

		Camera2D(const Viewport&);
		~Camera2D() { };

		void Update(float gameTime);

		glm::mat4 GetViewTransform() const { return m_ViewTransform; }
		glm::mat4 GetProjectionViewTransform() const { return m_ProjectionViewTransform; }

	private:

		glm::vec3 m_Origin;

		glm::mat4 m_ViewTransform;
		glm::mat4 m_ProjectionTransform;
		glm::mat4 m_ProjectionViewTransform;

		const Viewport& m_Viewport;

		void UpdateViewTransform();

	};

}