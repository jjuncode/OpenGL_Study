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

private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;// VAO_layout
    BufferUPtr m_vertexBuffer;      // VBO
    BufferUPtr m_indexBuffer;       // EBO

    TextureUPtr m_texture;  
    TextureUPtr m_texture2;

    glm::vec3 m_cameraPos{ glm::vec3(0.0f, 0.0f, 3.0f) };
    glm::vec3 m_cameraFront{ glm::vec3(0.0f, 0.0f, -1.0f) };
    glm::vec3 m_cameraUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
};

#endif // __CONTEXT_H__