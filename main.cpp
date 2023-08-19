#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WINDOW_WIDTH{ 800 };
const int WINDOW_HEIGHT{ 800 };
const char* const WINDOW_NAME{ "Test" };

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height);
}

int main(int argc, const char** argv) {
    // ������ �˸��� �α�
    SPDLOG_INFO("Start program");

    // glfw ���̺귯�� �ʱ�ȭ, �����ϸ� ���� ����� ����
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw ������ ����, �����ϸ� ���� ����� ����
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
        nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad�� Ȱ���� OpenGL �Լ� �ε�
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", (const char*)glVersion);

    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw ���� ����, ������ close ��ư�� ������ ���� ����
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}