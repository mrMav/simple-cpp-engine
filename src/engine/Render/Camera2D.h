
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

		float Zoom = 1.0f;
		float TargetZoom = Zoom;

		Camera2D(const Viewport& const);
		~Camera2D() { };

		void Update(float gameTime);

		glm::mat4 GetViewTransform() const { return m_ViewTransform; }
		glm::mat4 GetProjectionTransform() const { return m_ProjectionTransform; }

	private:

		glm::mat4 m_ViewTransform;
		glm::mat4 m_ProjectionTransform;

		const Viewport& const m_Viewport;

	};

}