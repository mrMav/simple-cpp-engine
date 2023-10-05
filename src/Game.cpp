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

    Game::Game(uint32_t windowWidth, uint32_t windowHeight, const char* windowTitle)
        : m_windowWidth(windowWidth), m_windowHeight(windowHeight)
    {
        if(windowTitle)
            m_windowTitle = windowTitle;
        else
            m_windowTitle = "New Game";

        m_viewport = Viewport(windowWidth, windowHeight);

    }

    Game::~Game()
    {
        delete[] m_screenQuadVertices;
        delete[] m_screenQuadIndices;

    }

    void Game::Run()
    {
        Init();
        Load();

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
            
            Input::PreUpdate();
            Update(delta);

            PreRender();
            Render(delta);  // calls the specific game render function.
            PostRender();

            // TODO: be moved to rendering class
            glFlush();

            Input::PostUpdate();  // TODO: this function to be moved to application level
                                  // must be called at the end of the gameloop, but before polling events
 
            //glfwSwapBuffers(window);
            glfwPollEvents();

        }

        // shutdown all systems
        Shutdown();

    }

    void Game::Load()
    {

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

        m_windowHandle = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle.c_str(), NULL, NULL);
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

        m_viewport.Set();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

    void Game::SetRenderTarget()
    {
        if(!useRenderTarget) return;

        m_screenQuad = std::make_shared<VertexArray>(&VertexPositionTexture::Attributes);
        
        m_screenQuadVertices = new VertexPositionTexture[4];
        m_screenQuadVertices[0].Position = glm::vec3(-1,  1, 0);  // top left
        m_screenQuadVertices[1].Position = glm::vec3( 1,  1, 0);  // top right
        m_screenQuadVertices[2].Position = glm::vec3( 1, -1, 0);  // bottom right
        m_screenQuadVertices[3].Position = glm::vec3(-1, -1, 0);  // bottom left

        m_screenQuadVertices[0].Texture = glm::vec2(0, 1);   // top left
        m_screenQuadVertices[1].Texture = glm::vec2(1, 1);   // top right
        m_screenQuadVertices[2].Texture = glm::vec2(1, 0);   // bottom right
        m_screenQuadVertices[3].Texture = glm::vec2(0, 0);   // bottom left

        m_screenQuad->SetVertices(m_screenQuadVertices, 4 * sizeof(VertexPositionTexture));

        m_screenQuadIndices = new uint16_t[6];
        m_screenQuadIndices[0] = 0;
        m_screenQuadIndices[1] = 1;
        m_screenQuadIndices[2] = 2;

        m_screenQuadIndices[3] = 0;
        m_screenQuadIndices[4] = 2;
        m_screenQuadIndices[5] = 3;

        m_screenQuad->SetIndices(m_screenQuadIndices, 6);

        m_renderTarget = std::make_shared<FrameBuffer>(renderTargetWidth, renderTargetHeight);

        std::string vertexSource = R"(#version 330 core

layout (location=0) in vec2 aPos;
layout (location=1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	TexCoords = aTexCoords;
})";

        std::string fragmentSource = R"(#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    FragColor = texture(screenTexture, TexCoords);
})";

        m_screenSpaceShader = std::make_shared<Shader>(true, vertexSource.c_str(), fragmentSource.c_str());

        m_viewport.SetWidth(renderTargetWidth);
        m_viewport.SetHeight(renderTargetHeight);
        m_viewport.Set();
        m_renderTarget->Bind();

    }

    void Game::Update(float delta)
    {

    }

    void Game::PreRender()
    {
        if (useRenderTarget)
        {
            glViewport(0, 0, renderTargetWidth, renderTargetHeight);
            m_renderTarget->Bind();
            glEnable(GL_DEPTH_TEST);
        }

    }

    void Game::PostRender()
    {
        if (useRenderTarget)
        {
            // draw the screen quad with the rendered framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, m_windowWidth, m_windowHeight);
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.8, 0.8, 0.8, 1);
            glClear(GL_COLOR_BUFFER_BIT); // only need to clear the color, since we do not perform depth or stencil here

            m_screenSpaceShader->use();
            m_screenQuad->Bind();
            m_renderTarget->BindTexture();
            m_screenQuad->DrawElements();
        }
    }

    void Game::Render(float delta)
    {
        
    }

    void Game::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_windowHandle);
        glfwTerminate();
    }


}
