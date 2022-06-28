#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <vector>
#include <limits>

#include "Engine/Engine.h"

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
    glm::vec3 color = glm::vec3(0, 1, 0);

    float lastDown = 0;
    float bestTime = std::numeric_limits<float>::max();

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
        angle += (3.14 / 360) * delta;

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

        if (Input::IsKeyJustDown(Key::J))
        {
            Input::PrintJoysticksList();
        }

        if (Input::IsButtonPressed(0, Button::ButtonA))
        {
            scaleplus = 25;
        }

        squareTransform = glm::translate(squarePosition);
        squareTransform = glm::scale(squareTransform, glm::vec3((sin(time) + 2) * 1.5 + scaleplus));
        squareTransform = glm::rotate(squareTransform, angle, glm::vec3(0, 0, 1));
        scaleplus *= 0.999;

        shader.use();
        shader.setVec3("uColor", color);
        shader.setFloat("uTime", time);
        shader.setMat4("uModel", squareTransform);
        shader.setMat4("uView", camera.GetViewTransform());
        shader.setMat4("uProjection", camera.GetViewProjectionTransform());

        va.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetDataCount(), GL_UNSIGNED_SHORT, 0);
        
        Input::PostUpdate();  // TODO: this function to be moved to application level
                          // must be called at the end of the gameloop, but before polling events
        
        glFlush();
        //glfwSwapBuffers(window);
        glfwPollEvents();

    }

    vb.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);

}