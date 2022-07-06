#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <vector>

#include "ShaderAttributes.h"

namespace Engine
{
        
    class VertexArray
    {

    public:
        VertexArray(const ShaderAttributes* attribs)
            : m_Attributes(attribs)
        {
            glGenVertexArrays(1, &m_Handle);
            Bind();
            SetAttributes();
        }

        ~VertexArray() {}

        void Bind() const
        {
            glBindVertexArray(m_Handle);
        }

        void Unbind() const
        {
            glBindVertexArray(0);
        }

        void Delete()
        {
            glDeleteBuffers(1, &m_Handle);
        }

    private:
    
        GLuint m_Handle;

        uint8_t m_AttribIndex = 0;

        const ShaderAttributes* m_Attributes;
        
        void SetAttributes()
        {
            
            for(auto const &attrib : m_Attributes->GetAttributes())
            {
                switch(attrib.Type)
                {
                    case AttributeType::Float3:
                    {
                        glVertexAttribPointer(m_AttribIndex, attrib.GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(attrib.Type), attrib.Normalized ? GL_TRUE : GL_FALSE,
                            m_Attributes->GetStride(), (void*)(attrib.Offset));
                        glEnableVertexAttribArray(m_AttribIndex);
                        m_AttribIndex++;

                        break;
                    }
                    case AttributeType::Float2:
                    {
                        // same as Float3, repeated code?

                        glVertexAttribPointer(m_AttribIndex, attrib.GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(attrib.Type), attrib.Normalized ? GL_TRUE : GL_FALSE,
                            m_Attributes->GetStride(), (void*)(attrib.Offset));
                        glEnableVertexAttribArray(m_AttribIndex);
                        m_AttribIndex++;                        
                        
                        break;

                    }

                }

            }

        }

    };

}