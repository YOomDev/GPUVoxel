
#include <chrono> // timing
#include <cstdio> // printf_s

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h> // window, openglcontext

#define WIDTH 640
#define HEIGHT 480

static const char* computeshaderSource = "";

int main(void) {
    GLFWwindow* window;
    // Initialize GLFW
    if (!glfwInit()) {
        printf_s("[ERROR-GLFW] Failed to initialize GLFW.");
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "GPUVoxel v0.1", NULL, NULL);
    if (!window) {
        printf_s("[ERROR-GLFW] Failed to create a window.");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        printf_s("[ERROR-GLEW] Failed to initialize GLEW.");
        glfwTerminate();
        return -1;
    }

    // Setup compute shaders
    GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShader, 1, &computeshaderSource, NULL);
    glCompileShader(computeShader);

    // Setup compute program
    GLuint computeProgram = glCreateProgram();
    glAttachShader(computeProgram, computeShader);
    glLinkProgram(computeProgram);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        
        // TODO: use compute
        // one buffer for output,
        // another for chunk load requests
        //glUseProgram(computeProgram);
        //glDispathCompute(WIDTH, HEIGHT, 1);
        //glMemoryBarrier(GL_ALL_BARRIER_BITS);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}