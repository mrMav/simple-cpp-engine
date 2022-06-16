#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>

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
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

    
    // ok, let's see how much I can do from memory

    float vertices[] = {
         0.0f,  0.9f, 0.0f,
        -0.9f, -0.9f, 0.0f,
         0.9f, -0.9f, 0.0f
    };

    const char *vertexShaderSource = "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\n";

    const char *fragmentShaderSource = "#version 460 core\n"
        "out vec4 FragColor;\n"
        "uniform vec3 uColor;\n"
        "uniform float uTime;"
        "void main(){\n"
        "   float v = sin(uTime) / 2.0 + 0.5;"
        "   FragColor = vec4(uColor.r, uColor.g, uColor.b * v, 1.0);\n"
        "}\n";

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Error compiling vertex shader\n" << infoLog << std::endl;
    }

    GLuint fragementShader;
    fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragementShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragementShader);

    glGetShaderiv(fragementShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragementShader, 512, nullptr, infoLog);
        std::cout << "Error compiling fragment shader\n" << infoLog << std::endl;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragementShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error linking shaders\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragementShader);

    GLuint vbo, vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
    
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
        GLuint vertexColorLocation = glGetUniformLocation(shaderProgram, "uColor");
        GLuint timeLocation = glGetUniformLocation(shaderProgram, "uTime");
        
        glUseProgram(shaderProgram);
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);
        glUniform1f(timeLocation, time);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}