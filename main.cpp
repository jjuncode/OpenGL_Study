#include "context.h"

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height);
void OnCursorPos(GLFWwindow* window, double x, double y);
void OnMouseButton(GLFWwindow* window, int button, int action, int modifier);

int main() {
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description{ nullptr };
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    // OpenGL 버전 로그 출력 
    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", (const char*)glVersion);

    // Context 초기화
    std::unique_ptr<Context> context = Context::Create();
    if (!context) {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }

    // Callback Function Setting
    glfwSetWindowUserPointer(window, context.get());
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetMouseButtonCallback(window, OnMouseButton);
    
    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        context->ProcessInput(window);
        context->Render();
        glfwSwapBuffers(window);
    }

    // 정리
    context.reset();

    glfwTerminate();
    return 0;
}

void OnKeyEvent(GLFWwindow* window,int key, int scancode, int action, int mods) 
{
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

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) 
{
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    context->Reshape(width,height);
    glViewport(0, 0, width, height);
}

void OnCursorPos(GLFWwindow* window, double x, double y) 
{
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    context->MouseMove(x, y);
} 

void OnMouseButton(GLFWwindow* window, int button, int action, int modifier)
{
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    context->MouseButton(button, action, x, y);
}