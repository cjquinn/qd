#include "Renderer/Buffer.h"

#include <glad/glad.h>

#include "Qd/Core/Assert.h"

namespace Qd::Renderer {
    IndexBuffer::IndexBuffer(uint32_t* indices, int32_t count) : count_{count} {
        glGenBuffers(1, &rendererId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<int32_t>(sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }

    VertexBuffer::VertexBuffer(uint32_t size) {
        glGenBuffers(1, &rendererId_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
        glGenBuffers(1, &rendererId_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }

    void VertexBuffer::setData(void* data, uint32_t size) const {
        QD_CORE_ASSERT(rendererId_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
}
