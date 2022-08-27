#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "OpenGL/GLUtils.h"
#include "Input/Input.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

namespace Engine
{

    Game::Game(uint32_t screenWidth, uint32_t screenHeight, char* windowTitle)
        : m_screenWidth(screenWidth), m_screenHeight(m_screenHeight)
    {
        if(windowTitle)
            m_windowTitle = windowTitle;
        else
            m_windowTitle = "New Game";
    }

    void Game::Run()
    {
        Init();

        // start the game loop here:
        
        // TODO: make a proper time keeping class
        double time = 0;
        double delta = 0;

        glfwSetTime(0);
        while (!glfwWindowShouldClose(m_windowHandle))
        {
            double newTime = glfwGetTime();
            delta = newTime - time;
            time = newTime;

            Update(delta);
            Render(delta);

            glFlush();

            //glfwSwapBuffers(window);
            glfwPollEvents();

        }   

    }

    void Game::Init()
    {

        // init glfw
        // if this fails, we cannot proceed.

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

        // creating the system window
        // also hard fail in case of error

        m_windowHandle = glfwCreateWindow(m_screenWidth, m_screenHeight, m_windowTitle.c_str(), NULL, NULL);
        if (!m_windowHandle)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowAttrib(m_windowHandle, GLFW_RESIZABLE, GLFW_FALSE);

        glfwMakeContextCurrent(m_windowHandle);


        // load glad, but hard fail in case of error
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // configure opengl context
        // TODO: move to renderer init
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.392, 0.584, 0.929, 1);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Set the function that will be triggered by the callback, the second parameter
        // is the data parameter of the callback, it can be useful for different
        // contexts but isn't necessary for our simple use case.
        glDebugMessageCallback(GLUtils::GLDebugMessageCallback, 0);

        // set the log level
        GLLogLevel = GLErrorLogLevel::Low;


        // initiates the state of the input system
        Input::Init(m_windowHandle);


        /* imgui */
        // TODO: Move to a imgui wrapper class?
        // from thhe examples folder
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io; // what

        ImGui::StyleColorsDark();

        //backends
        ImGui_ImplGlfw_InitForOpenGL(m_windowHandle, true);
        ImGui_ImplOpenGL3_Init(NULL);

    }

    void Game::Update(float delta)
    {

    }

    void Game::Render(float delta)
    {
        
    }

    void Game::Shutdown()
    {

    }


}