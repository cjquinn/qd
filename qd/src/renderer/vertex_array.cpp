#include "qd/renderer/vertex_array.h"

#include <glad/glad.h>

#include <unordered_map>

#include "qd/core/assert.h"
#include "renderer/buffer.h"

namespace {
GLenum GetGlEnum(qd::renderer::ShaderType shader_type) {
  static const std::unordered_map<qd::renderer::ShaderType, GLenum>
      kShaderTypeToGLenum = {{qd::renderer::ShaderType::kFloat, GL_FLOAT}};
  return kShaderTypeToGLenum.at(shader_type);
}

void SetVertexLayout(
    std::initializer_list<qd::renderer::VertexAttribute> vertex_attributes) {
  std::vector<qd::renderer::VertexAttribute> layout{vertex_attributes};

  int32_t stride{0};
  for (auto& vertex_attribute : layout) {
    stride +=
        vertex_attribute.count * static_cast<int32_t>(vertex_attribute.type);
    vertex_attribute.offset = stride;
  }

  uint32_t index{0};
  size_t offset{0};
  for (const auto& vertex_attribute : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vertex_attribute.count,
                          GetGlEnum(vertex_attribute.type),
                          vertex_attribute.is_normalized ? GL_TRUE : GL_FALSE,
                          stride, (void*)offset);
    offset += vertex_attribute.offset;
    index++;
  }
}
}  // namespace

namespace qd::renderer {
VertexArray::VertexArray() = default;

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &renderer_id_); }

void VertexArray::Init() {
  glGenVertexArrays(1, &renderer_id_);
  glBindVertexArray(renderer_id_);
}

void VertexArray::Bind() const {
  QD_CORE_ASSERT(renderer_id_);

  glBindVertexArray(renderer_id_);
}

void VertexArray::SetVertexBuffer(
    uint32_t size, std::initializer_list<VertexAttribute> vertex_attributes) {
  QD_CORE_ASSERT(renderer_id_);

  vertex_buffer_.reset(new VertexBuffer{size});
  SetVertexLayout(vertex_attributes);
}

void VertexArray::SetVertexBuffer(
    float* vertices, uint32_t size,
    std::initializer_list<VertexAttribute> vertex_attributes) {
  QD_CORE_ASSERT(renderer_id_);

  vertex_buffer_.reset(new VertexBuffer{vertices, size});
  SetVertexLayout(vertex_attributes);
}

void VertexArray::SetVertexData(void* data, uint32_t size) {
  vertex_buffer_->SetData(data, size);
}

void VertexArray::SetIndexBuffer(uint32_t* indices, int32_t count) {
  QD_CORE_ASSERT(renderer_id_);

  index_buffer_.reset(new IndexBuffer{indices, count});
}

int32_t VertexArray::GetCount() const {
  if (index_buffer_) {
    return index_buffer_->GetCount();
  }

  return 0;
}
}  // namespace qd::renderer
