#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <vector>
#include <limits>

#include "Engine/Engine.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

using namespace Engine;

int main()
{
    std::cout << "We meet again." << std::endl;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    uint32_t gameWidth = 1280, gameHeight = 720;

    GLFWwindow* window = glfwCreateWindow(gameWidth, gameHeight, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {        
        std::cout << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    // Set the function that will be triggered by the callback, the second parameter
    // is the data parameter of the callback, it can be useful for different
    // contexts but isn't necessary for our simple use case.
    glDebugMessageCallback(GLUtils::GLDebugMessageCallback, 0);

    // set the log level
    GLLogLevel = GLErrorLogLevel::Low;
    
    Input::Init(window);    
    
    std::vector<VertexPositionColor> vertexDataTriangle =
    {
        VertexPositionColor{glm::vec3( 0.0f, 40.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 20.0f, 0.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)}
    };

    std::vector<VertexPositionColor> vertexDataSquare =
    {
        VertexPositionColor{glm::vec3(-25,   25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 25,   25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 25,  -25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3(-25,  -25, 0), glm::vec3(0.906f,0.235f, 0.0f)}
    };

    std::vector<uint16_t> triangleIndices = 
    {
        0, 1, 2
    };

    std::vector<uint16_t> squareIndices = 
    {
        0, 1, 2,
        0, 2, 3
    };

    Shader shader("Shaders/vertex.vert", "Shaders/fragment.frag");
    
    VertexBuffer vb = VertexBuffer(&(vertexDataSquare[0]), vertexDataSquare.size() * sizeof(VertexPositionColor));
    VertexArray va(&VertexPositionColor::Attributes);
    IndexBuffer ib = IndexBuffer(&squareIndices[0], squareIndices.size());

    Viewport viewport(gameWidth, gameHeight);
    viewport.Set();

    Camera2D camera(viewport);
    
    glm::mat4 squareTransform(1.0f);
    glm::vec3 squarePosition(viewport.Width() / 2.0f, viewport.Height() / 2.0f, 0.0f);

    float time = 0;
    float delta;
    float angle = 0;
    float scaleplus = 0;
    glm::vec4 color = glm::vec4(1, 1, 1, 1);

    float deadzone = 0.21f; // I blame Rocket League
    Input::SetDeadZone(0, deadzone);

    float lastDown = 0;
    float bestTime = std::numeric_limits<float>::max();


    /* imgui */
    // from thhe examples folder
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; // what

    ImGui::StyleColorsDark();

    //backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);

    bool show_demo_window = true;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.392, 0.584, 0.929, 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Input::PreUpdate();

        camera.Update(0.0f);

        // update square transform
        float newTime = glfwGetTime();
        delta = newTime - time;
        time = glfwGetTime();
        angle -= 10 * delta;

        if (Input::IsKeyPressed(Key::Up))
        {
            angle += 2.0f * delta;
        }

        if (Input::IsKeyJustDown(Key::Down) || Input::IsKeyJustDown(Key::Up))
        {
            bestTime = (time - lastDown) < bestTime ? (time - lastDown) : bestTime;
            lastDown = time;
            std::cout << "Down was just pressed at runtime time (ms): " << time * 1000.0f << " best time (ms): " << bestTime * 1000.0f <<  " Delta time (ms) is: " << delta * 1000.0f << std::endl;
        }

        if (Input::IsKeyJustDown(Key::KPAdd))
        {
            deadzone += 0.01f;
            Input::SetDeadZone(0, deadzone);
            std::cout << deadzone << std::endl;
        }

        if (Input::IsKeyJustDown(Key::KPSubtract))
        {
            deadzone -= 0.01f;
            Input::SetDeadZone(0, deadzone);
            std::cout << deadzone << std::endl;
        }

        if (Input::IsButtonJustDown(0, GamePadButton::ButtonY) || Input::IsButtonJustDown(0, GamePadButton::ButtonX))
        {
            bestTime = (time - lastDown) < bestTime ? (time - lastDown) : bestTime;
            lastDown = time;
            std::cout << "pressed at runtime time (ms): " << time * 1000.0f << " best time (ms): " << bestTime * 1000.0f << " Delta time (ms) is: " << delta * 1000.0f << std::endl;
        }

        if (Input::IsKeyJustDown(Key::J))
        {
            Input::PrintJoysticksList();
        }

        if (Input::IsButtonPressed(0, GamePadButton::ButtonA))
        {
            angle += 180.0f * delta;
        }

        if (Input::IsButtonJustDown(0, GamePadButton::ButtonB))
        {
            scaleplus = 25;
        }

        float speed = 600.0f;
        squarePosition.x += Input::GetAxisStrength(0, GamePadAxis::GamePadAxisLeftX)  * speed * delta;
        squarePosition.y += Input::GetAxisStrength(0, GamePadAxis::GamePadAxisLeftY) * speed * delta;

        color.r = Input::GetAxisStrength(0, GamePadAxis::GamePadAxisLeftTrigger) * -1;
        color.g =  color.r;
        color.b =  color.r;
        color.a = Input::GetAxisStrength(0, GamePadAxis::GamePadAxisRightTrigger) * -1;

        //std::cout << glm::to_string(color) << std::endl;

        squareTransform = glm::translate(squarePosition);
        squareTransform = glm::scale(squareTransform, glm::vec3((sin(time) + 2) * 1.5 + scaleplus));
        squareTransform = glm::rotate(squareTransform, glm::radians(angle), glm::vec3(0, 0, 1));
        scaleplus *= 0.999;

        shader.use();
        shader.setVec4("uColor", color);
        shader.setFloat("uTime", time);
        shader.setMat4("uModel", squareTransform);
        shader.setMat4("uView", camera.GetViewTransform());
        shader.setMat4("uProjection", camera.GetProjectionViewTransform());

        va.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetDataCount(), GL_UNSIGNED_SHORT, 0);
        
        Input::PostUpdate();  // TODO: this function to be moved to application level
                          // must be called at the end of the gameloop, but before polling events
        


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glFlush();

        //glfwSwapBuffers(window);
        glfwPollEvents();

    }

    vb.Delete();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);

}