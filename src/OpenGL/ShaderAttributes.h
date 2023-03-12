#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>


namespace Engine
{
    // thanks cherno
    enum class AttributeType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    GLenum ShaderDataTypeToOpenGLBaseType(const AttributeType type);

    struct ShaderAttrib
    {
        AttributeType Type;
        size_t Size;
        size_t Offset = 0;
        bool Normalized = false;

        uint32_t GetComponentCount() const
		{
            // thanks again cherno
			switch (Type)
			{
				case AttributeType::Float:   return 1;
				case AttributeType::Float2:  return 2;
				case AttributeType::Float3:  return 3;
				case AttributeType::Float4:  return 4;
				case AttributeType::Mat3:    return 3; // 3* float3
				case AttributeType::Mat4:    return 4; // 4* float4
				case AttributeType::Int:     return 1;
				case AttributeType::Int2:    return 2;
				case AttributeType::Int3:    return 3;
				case AttributeType::Int4:    return 4;
				case AttributeType::Bool:    return 1;
			}

			return 0;
		}

        const std::string String() const
        {
            using namespace std;

            string s;
            s.append("AttribType: ");
            s.append(to_string((int)Type));
            s.append(" Size: ");
            s.append(to_string(Size));
            s.append(" Offset: ");
            s.append(to_string(Offset));

            return s;

        }
        
    };

    class ShaderAttributes
    {   
    
    public:
    
        ShaderAttributes(std::initializer_list<ShaderAttrib> attribs)
            : m_Attributes(attribs)
        {
            CalculateOffsetsAndStride();
        }

        const std::vector<ShaderAttrib>& GetAttributes() const
        {
            return m_Attributes;
        }

        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for(auto &attrib : m_Attributes)
            {
                attrib.Offset = offset; 
                offset += attrib.Size;
                m_Stride += attrib.Size;
            }
        }

        int GetStride() const
        {
            return m_Stride;
        }

        void PrintAttribs() const
        {
            for(auto const &attrib : m_Attributes)
                std::cout << attrib.String() << std::endl;
        }
    
    private:

        std::vector<ShaderAttrib> m_Attributes;

        int m_Stride;

    };

    struct VertexPositionTexture
    {        
        // init in ShaderAttributes.cpp
        const static ShaderAttributes Attributes;

        glm::vec3 Position;
        glm::vec2 Texture;

        VertexPositionTexture(glm::vec3 pos, glm::vec2 tex)
            : Position(pos), Texture(tex)
        {
            
        }

        VertexPositionTexture()
        {
            Position = glm::vec3(0);
            Texture = glm::vec2(0);
        }

    };

    struct VertexPositionColor
    {
        // init in ShaderAttributes.cpp
        const static ShaderAttributes Attributes;
        
        glm::vec3 Position;
        glm::vec3 Color;

        VertexPositionColor(glm::vec3 pos, glm::vec3 color)
            : Position(pos), Color(color)
        {
            
        }
    };

    struct VertexPositionColorTexture
    {
        // init in ShaderAttributes.cpp
        const static ShaderAttributes Attributes;

        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 Texture;

        VertexPositionColorTexture(glm::vec3 pos, glm::vec3 color, glm::vec2 texture)
            : Position(pos), Color(color), Texture(texture)
        {

        }

        VertexPositionColorTexture()
        {
            Position = glm::vec3(0);
            Color    = glm::vec3(0);
            Texture  = glm::vec2(0);
        }
    };
    
}