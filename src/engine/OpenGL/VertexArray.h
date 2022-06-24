#pragma once

#include <glad/glad.h>

#include <stdio.h>
#include <vector>
#include <memory>

#include "ShaderAttributes.h"

namespace Engine
{
        
    class VertexArray
    {

    public:
        VertexArray()
        {
            glGenVertexArrays(1, &m_Handle);
            Bind();

            

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

        //void SetAttributes()


    private:

        GLuint m_Handle;

        uint8_t m_AttribIndex = 0;

        ShaderAttributes m_Attributes;

    };

}