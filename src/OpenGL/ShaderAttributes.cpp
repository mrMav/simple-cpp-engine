
#include "ShaderAttributes.h"

namespace Engine
{
    GLenum ShaderDataTypeToOpenGLBaseType(const AttributeType type)
	{
        // ty cherno x3
		switch (type)
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

		return 0;
	}

    const ShaderAttributes VertexPositionTexture::Attributes = ShaderAttributes(
        {
            { AttributeType::Float3, sizeof(Position) },
            { AttributeType::Float2, sizeof(Texture)  }
        }
    );

    const ShaderAttributes VertexPositionColor::Attributes = ShaderAttributes(
        {
            { AttributeType::Float3, sizeof(Position) },
            { AttributeType::Float3, sizeof(Color)    }
        }
    );

    const ShaderAttributes VertexPositionColorTexture::Attributes = ShaderAttributes(
        {
            { AttributeType::Float3, sizeof(Position) },
            { AttributeType::Float3, sizeof(Color)    },
            { AttributeType::Float3, sizeof(Texture)  }
        }
    );


}