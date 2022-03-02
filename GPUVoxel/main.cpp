// std libraries
#include <chrono> // timing
#include <cstdio> // printf_s
#include <vector>

// OpenGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h> // window, openglcontext

// Math
#include <glm/vec3.hpp>

#define WIDTH 640
#define HEIGHT 480

struct Camera {
    glm::vec3 position = { 0, 0, 0 };
    glm::vec3 direction = { 0, 0, 0 };
};

struct ChunkData {
    uint32_t voxel[16 * 16 * 16] = { 0 }; // to big to add location to this struct as that would overflow the max byte size of a object, so ChunkRef exists to add that functionality back
};

struct ChunkRef {
    bool isUsed = false;
    int location[3] = { 0,0,0 };
};

struct Material {
    uint32_t type = 0; // 0 = AIR, 1 = SOLID, 2 = REFLECTIVE, 3 = REFRACTIVE
    glm::vec3 color = {}; // unused in AIR
    float roughness = 0.0f; // unused in AIR
    float typeStrength = 0.0f; // only used on type = REFRACTIVE and type = AIR
};

static const char* computeshaderSource = ""; // TODO

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

    // Setup data
    Camera cam = { {-8,4,-8}, {4,-3,8} };
    cam.direction /= cam.direction.length(); // normalize direction
    Material material[4];
    material[0] = { 0, {0.5,0.7,0.3}, 0.0f, 1.0f }; // AIR
    material[0] = { 1, {0.3,0.5,0.7}, 0.3f, 1.0f }; // SOLID
    material[0] = { 2, {0.3,0.7,0.5}, 0.1f, 1.0f }; // REFLECTIVE
    material[0] = { 3, {0.7,0.3,0.5}, 0.0f, 1.325f }; // REFRACTIVE

    // splitting the chunk data and location makes it not overflow
    std::vector<ChunkRef> world;
    std::vector<ChunkData> worldInfo;
    world.push_back(ChunkRef());
    worldInfo.push_back(ChunkData());

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
        // gameplay loop
        // TODO

        // Bind data to compute shader
        // TODO

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        
        // TODO: use compute
        // one buffer for output,
        // another for chunk load requests
        glUseProgram(computeProgram);
        glDispatchCompute(WIDTH, HEIGHT, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}