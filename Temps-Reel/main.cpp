// Include standard headers
#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "shader.h"

using namespace std;

void APIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    cout << message << endl;
}

int main() {
    // Initialise GLFW
    glewExperimental = true; // Needed for core profile

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

// Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 800, 800, "Gamagora", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glDebugMessageCallback(opengl_error_callback, nullptr);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Shader
    const auto vertex = MakeShader(GL_VERTEX_SHADER, "../shader.vert");
    const auto fragment = MakeShader(GL_FRAGMENT_SHADER, "../shader.frag");
    const auto program = AttachAndLink({vertex, fragment});

    glUseProgram(program);

    GLuint vbo, vao, vbo_color;

    vector<float> vertices;

    vertices.push_back(-0.5);
    vertices.push_back(0.5);
    vertices.push_back(0.5);
    vertices.push_back(0.5);
    vertices.push_back(-0.5);
    vertices.push_back(-0.5);

    vertices.push_back(0.5);
    vertices.push_back(-0.5);

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    cout << "Nb points: " << vertices.size() << endl;

    vector<float> colors {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        1, 1, 1
    };

    glCreateBuffers(1, &vbo_color);
    glNamedBufferData(vbo_color, sizeof(colors[0]) * colors.size(), colors.data(), GL_DYNAMIC_DRAW);

    glCreateVertexArrays(1, &vao);
    const auto index = 0;
    const auto binding_point = 0;

    glEnableVertexArrayAttrib(vao, index);
    glVertexArrayAttribFormat(vao, index, 2, GL_FLOAT, GL_FALSE, 0);

    glVertexArrayAttribBinding(vao, index, binding_point);
    glVertexArrayVertexBuffer(vao, binding_point, vbo, 0, 2 * sizeof(float));

    const auto index_colors = 1;
    const auto binding_point_colors = 1;

    glEnableVertexArrayAttrib(vao, index_colors);
    glVertexArrayAttribFormat(vao, index_colors, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, index_colors, binding_point_colors);
    glVertexArrayVertexBuffer(vao, binding_point_colors, vbo_color, 0, 3 * sizeof(float));

    glClearColor(0.5f, 0.7f, 0.1f, 1.0f);
    float previousTime = glfwGetTime();

    do{
        int w, h;
        glfwGetWindowSize(window, &w, &h);

        glViewport(0, 0, w, h);

        glClear( GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 2);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}