#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderAttributes.h"

namespace Engine
{
        
    class VertexArray
    {

    public:
        VertexArray(const ShaderAttributes* attribs)
            : m_Attributes(attribs)
        {
            m_VertexBuffer = VertexBuffer();
            m_IndexBuffer = IndexBuffer();

            glGenVertexArrays(1, &m_Handle);
            Bind();

            SetAttributes();
        }

        ~VertexArray() {}

        void Bind() const
        {
            glBindVertexArray(m_Handle);
        }

        void SetVertices(const void* data, size_t size)
        {
            m_VertexBuffer.Bind();
            m_VertexBuffer.SetData(data, size);
        }

        void SetIndices(const void* data, size_t size)
        {
            m_IndexBuffer.Bind();
            m_IndexBuffer.SetData(data, size);
        }

        void Unbind() const
        {
            glBindVertexArray(0);
        }

        void Delete()
        {
            m_IndexBuffer.Delete();
            m_VertexBuffer.Delete();
            glDeleteBuffers(1, &m_Handle);
        }

        void DrawElements()
        {
            Bind();
            m_VertexBuffer.Bind();  // TODO: check all this binding need and order
            m_IndexBuffer.Bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer.GetDataCount(), GL_UNSIGNED_SHORT, 0);
        }

    private:
    
        GLuint m_Handle;

        VertexBuffer m_VertexBuffer;

        IndexBuffer m_IndexBuffer;

        uint8_t m_AttribIndex = 0;

        const ShaderAttributes* m_Attributes;
        
        void SetAttributes()
        {
            
            for(auto const &attrib : m_Attributes->GetAttributes())
            {
                switch(attrib.Type)
                {
                    // TODO: check repeated code in the stride calculation for vectors

                    case AttributeType::Float4:
                    {
                        glVertexAttribPointer(m_AttribIndex, attrib.GetComponentCount(),
                            ShaderDataTypeToOpenGLBaseType(attrib.Type), attrib.Normalized ? GL_TRUE : GL_FALSE,
                            m_Attributes->GetStride(), (void*)(attrib.Offset));
                        glEnableVertexAttribArray(m_AttribIndex);
                        m_AttribIndex++;

                        break;
                    }
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