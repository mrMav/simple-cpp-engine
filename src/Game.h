#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

#include "Render/Viewport.h"

namespace Engine
{

    class Game
    {
        public:

            Game(uint32_t screenWidth, uint32_t screenHeight, const char* windowTitle);
            ~Game() { };

            void virtual Run();
            void virtual Load();
            void virtual Update(float delta);
            void virtual Render(float delta);
            void Shutdown();

            Viewport& GetViewport() { return m_viewport; }
            

        private:
            
            void Init();

            uint32_t m_screenWidth;
            uint32_t m_screenHeight;

            GLFWwindow* m_windowHandle;
            std::string m_windowTitle;

            Viewport m_viewport;

    };

}
