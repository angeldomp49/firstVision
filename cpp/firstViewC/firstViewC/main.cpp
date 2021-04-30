
#define GLEW_STATIC

#include"glew.h"
#include"glfw3.h"

#include "Shape.cpp"
#include "Shader.cpp"
#include "ShaderProgram.cpp"

#include<iostream>

void init(void);
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;

int main() {
    init();

    GLint success;
    GLchar infoLog[512];

    // vertex shader
    Shader* vertexShader = new Shader("vertex.vert", GL_VERTEX_SHADER);
    
    // fragment shader
    Shader* fragmentShader = new Shader("fragment.frag", GL_FRAGMENT_SHADER);

    ShaderProgram* shaderProgram = new ShaderProgram();

    shaderProgram->addShader(vertexShader->obj);
    shaderProgram->addShader(fragmentShader->obj);

    shaderProgram->link();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    GLfloat vertices[] = {
    -0.5f,  0.5f, 0.0f, //top left
     0.5f,  0.5f, 0.0f, //top right
    -0.5f, -0.5f, 0.0f, //bottom left
     0.5f, -0.5f, 0.0f  //bottom right
    };

    GLuint indices[] = {
        0,1,2,
        1,2,3
    };

    Shape* rectangle = new Shape( vertices, 12, indices, 6 );

    rectangle->prepare();

    while (!glfwWindowShouldClose(window)) {
        shaderProgram->use();
        rectangle->render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    rectangle->clean();
    shaderProgram->clean();

    glfwTerminate();
    return 0;
}

void init() {
    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (nullptr == window)
    {
        glfwTerminate();
        std::cout << "Failed to create Window object" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);


    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, closeOnEsc);
}

void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}