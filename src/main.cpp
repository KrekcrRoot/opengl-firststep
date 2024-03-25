#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include <iostream>

void framebuffer_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Title", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "WINDOW ERROR\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD LOAD ERROR\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_callback);

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0,
            0, 0.5f, 0,
            0.5f, -0.5f, 0
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 3, nullptr);
    glEnableVertexAttribArray(0);


    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;
}
