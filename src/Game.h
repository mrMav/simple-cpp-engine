#pragma once

#include <GLFW/glfw3.h>

namespace Engine
{

    class Game
    {
        public:

            Game(uint32_t screenWith, uint32_t screenHeight, char* windowTitle);
            ~Game();

            void Run();
            void Update(float delta);
            void Render(float delta);
            void Shutdown();

            uint32_t GetScreenWidth()  { return m_screenWidth;  }
            uint32_t GetScreenHeight() { return m_screenHeight; }

        private:
            
            void Init();

            uint32_t m_screenWidth;
            uint32_t m_screenHeight;

            GLFWwindow* m_windowHandle;
            std::string m_windowTitle;

    };

}