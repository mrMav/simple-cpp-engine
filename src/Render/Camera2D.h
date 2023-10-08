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
		float Zoom;

		Camera2D(Viewport&);
		~Camera2D() { };

		void Update(float gameTime);

		glm::vec2 ScreenToWorld(const glm::vec2& pos);
		glm::vec2 ScreenToWorld(int x, int y);
		glm::vec2 WorldToScreen(const glm::vec2& pos);
		glm::vec2 WorldToScreen(int x, int y);

		glm::mat4 GetViewTransform() const { return m_ViewTransform; }
		glm::mat4 GetProjectionTransform() const { return m_ProjectionTransform; }
		Viewport& GetViewport() const { return m_Viewport; };
		glm::vec2 GetCameraDisplaySize() const;

		void SetViewport(Viewport& v);
		
	private:

		glm::vec3 m_Origin;

		glm::mat4 m_ViewTransform;
		glm::mat4 m_ProjectionTransform;

		Viewport& m_Viewport;

		void UpdateProjection();
		void UpdateOrigin();

	};

}