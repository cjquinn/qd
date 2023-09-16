#include "buffer.h"

#include <glad/glad.h>

#include "qd/core/assert.h"

namespace qd::renderer {
IndexBuffer::IndexBuffer(uint32_t* indices, int32_t count) : count_{count} {
  glGenBuffers(1, &renderer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               count * static_cast<int32_t>(sizeof(uint32_t)), indices,
               GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &renderer_id_); }

VertexBuffer::VertexBuffer(uint32_t size) {
  glGenBuffers(1, &renderer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
  glGenBuffers(1, &renderer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &renderer_id_); }

void VertexBuffer::SetData(void* data, uint32_t size) const {
  QD_CORE_ASSERT(renderer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
}  // namespace qd::renderer
