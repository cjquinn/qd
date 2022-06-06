#include "Renderer/Buffer.h"

#include <glad/glad.h>

namespace Qd::Renderer {

    IndexBuffer::IndexBuffer(uint32_t* indices, int32_t count) {
        glGenBuffers(1, &rendererId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<uint32_t>(sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
        glGenBuffers(1, &rendererId_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }
}
