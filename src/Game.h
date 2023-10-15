#pragma once

#include <iostream>
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/Shader.h"
#include "Render/Viewport.h"

// glfw to be included only after glad
#include <GLFW/glfw3.h>

#include "Internal.h"
#include "StateManager.h"

namespace Engine
{
    class Game
    {
        public:

            Game(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle);
            ~Game();

            void virtual Run();
            void virtual Load();
            void virtual Shutdown();

            Viewport& GetViewport() { return m_viewport; }
            void SetRenderTarget();
            
            bool useRenderTarget = false;
            uint32_t renderTargetWidth;
            uint32_t renderTargetHeight;

        private:
            
            
            void Init();
            void PreRender();
            void PostRender();

            uint32_t m_windowWidth;
            uint32_t m_windowHeight;

            // Properties for our render target.
            // Ideally, this is to be setup in the GraphicsDevice
            // or RenderServer class type.
            // It will work for now.
            Ref<VertexArray> m_screenQuad;
            VertexPositionTexture m_screenQuadVertices[4];
            uint16_t m_screenQuadIndices[6];

            Ref<FrameBuffer> m_renderTarget;
            Ref<Shader> m_screenSpaceShader;

            GLFWwindow* m_windowHandle;
            std::string m_windowTitle;

            Viewport m_viewport;
            
    };

}
