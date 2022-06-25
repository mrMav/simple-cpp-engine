#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <vector>

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
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

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
    
    // ok, let's see how much I can do from memory

    std::vector<VertexPositionColor> vertexDataTriangle =
    {
        VertexPositionColor{glm::vec3( 0.0f,  0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        VertexPositionColor{glm::vec3( 0.9f, -0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        VertexPositionColor{glm::vec3(-0.9f, -0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)}
    };

    std::vector<VertexPositionColor> vertexDataSquare =
    {
        VertexPositionColor{glm::vec3(-0.9f,  0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        VertexPositionColor{glm::vec3( 0.9f,  0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        VertexPositionColor{glm::vec3( 0.9f, -0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)},
        VertexPositionColor{glm::vec3(-0.9f, -0.9f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)}
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
    
    VertexBuffer vb = VertexBuffer(&(vertexDataTriangle[0]), vertexDataTriangle.size() * sizeof(VertexPositionColor));
    VertexArray va(&VertexPositionColor::Attributes);
    IndexBuffer ib = IndexBuffer(&triangleIndices[0], triangleIndices.size());

    //Viewport
    

    float time;
    glm::vec3 color = glm::vec3(0.85, 0.4, 0.6);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        time = glfwGetTime();

        shader.use();
        shader.setVec3("uColor", color);
        shader.setFloat("uTime", time);

        va.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetDataCount(), GL_UNSIGNED_SHORT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vb.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);

}