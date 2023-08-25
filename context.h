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
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;// VAO_layout
    BufferUPtr m_vertexBuffer;      // VBO
    BufferUPtr m_indexBuffer;       // EBO

    TextureUPtr m_texture;  
    TextureUPtr m_texture2;
};

#endif // __CONTEXT_H__