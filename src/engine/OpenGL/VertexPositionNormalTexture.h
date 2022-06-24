#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// thanks cherno
enum class AttributeType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

struct VertexPositionNormalTexture {

public:

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;

	VertexPositionNormalTexture(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
		: position(pos), normal(norm), texture(tex)
	{
		
	}

	VertexPositionNormalTexture(float x, float y, float z, float nx, float ny, float nz, float u, float v)
	{
		position = glm::vec3(x, y, z);
		normal = glm::vec3(nx, ny, nz);
		texture = glm::vec2(u, v);
	}

	const uint8_t static GetStride()
	{
		return sizeof(position) + sizeof(normal) + sizeof(texture);
	}

	static GLenum GetOpenGLType(AttributeType type)
	{
		// thanks again cherno
		switch(type)
		{
			case AttributeType::Float:    return GL_FLOAT;
			case AttributeType::Float2:   return GL_FLOAT;
			case AttributeType::Float3:   return GL_FLOAT;
			case AttributeType::Float4:   return GL_FLOAT;
			case AttributeType::Mat3:     return GL_FLOAT;
			case AttributeType::Mat4:     return GL_FLOAT;
			case AttributeType::Int:      return GL_INT;
			case AttributeType::Int2:     return GL_INT;
			case AttributeType::Int3:     return GL_INT;
			case AttributeType::Int4:     return GL_INT;
			case AttributeType::Bool:     return GL_BOOL;
		}
	}

	const std::string GetString() const {

		std::string s;

		s.append("P: ");
		s.append(glm::to_string(position));

		s.append(" N: ");
		s.append(glm::to_string(normal));
		
		s.append(" T: ");
		s.append(glm::to_string(texture));

		return s;

	}

};

