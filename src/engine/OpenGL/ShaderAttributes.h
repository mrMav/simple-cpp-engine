#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdio.h>
#include <vector>


namespace Engine
{
    
    // thanks cherno
    enum class AttributeType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    struct ShaderAttrib
    {
        AttributeType Type;
        size_t Size;
        size_t Offset = 0;

        const std::string String()
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

        const std::vector<ShaderAttrib>* const GetAttributes() const
        {
            return &m_Attributes;
        }

        void CalculateOffsetsAndStride()
        {
            size_t offset = 0;
            m_Stride = 0;
            for(ShaderAttrib &attrib : m_Attributes)
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
            for(ShaderAttrib attrib : m_Attributes)
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
    
}