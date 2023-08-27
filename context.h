#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"
#include "texture.h"

CLASS_PTR(Context)
class Context {
public:
    static ContextUPtr Create();
    void Render();
    void ProcessInput(GLFWwindow* window);
    void Reshape(int width, int height);

    void MouseMove(double x, double y);
    void MouseButton(int button, int action, double x, double y);

private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;// VAO_layout
    BufferUPtr m_vertexBuffer;      // VBO
    BufferUPtr m_indexBuffer;       // EBO

    TextureUPtr m_texture;  
    TextureUPtr m_texture2;

    int m_width{ WINDOW_WIDTH };
    int m_height{ WINDOW_HEIGHT };

    // camera
    glm::vec3 m_cameraPos{ glm::vec3(0.0f, 0.0f, 3.0f) };
    glm::vec3 m_cameraFront{ glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
    
    float m_cameraPitch{ 0.0f };
    float m_cameraYaw{ 0.0f };

    bool m_cameraControl{ false };
    glm::vec2 m_prevMousePos{ glm::vec2(0.0f) };

    // clear color 
    glm::vec4 m_clearColor{ glm::vec4(0.1f, 0.2f, 0.3f, 0.0f) };    

    // light parameter
    struct Light {
        glm::vec3 position{ glm::vec3(3.0f, 3.0f, 3.0f) };
        glm::vec3 ambient{ glm::vec3(0.1f, 0.1f, 0.1f) };
        glm::vec3 diffuse{ glm::vec3(0.5f, 0.5f, 0.5f) };
        glm::vec3 specular{ glm::vec3(1.0f, 1.0f, 1.0f) };
    };
    Light m_light;

    // material parameter
    struct Material {
        glm::vec3 ambient{ glm::vec3(1.0f, 0.5f, 0.3f) };
        glm::vec3 diffuse{ glm::vec3(1.0f, 0.5f, 0.3f) };
        glm::vec3 specular{ glm::vec3(0.5f, 0.5f, 0.5f) };
        float shininess{ 32.0f };
    };
    Material m_material;

    // animation
	bool m_animation{ true };
};

#endif // __CONTEXT_H__