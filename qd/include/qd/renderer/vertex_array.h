#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

namespace qd::renderer {
class IndexBuffer;
class VertexBuffer;

enum class ShaderType : uint32_t {
  kFloat = 4,
};

struct VertexAttribute {
  VertexAttribute(ShaderType type, int32_t count, bool is_normalized = false)
      : count{count}, is_normalized{is_normalized}, type{type} {}

  ShaderType type;
  int32_t count;
  bool is_normalized;
  size_t offset{0};
};

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void Init();
  void Bind() const;

  void SetVertexBuffer(
      uint32_t size, std::initializer_list<VertexAttribute> vertex_attributes);
  void SetVertexBuffer(
      float* vertices, uint32_t size,
      std::initializer_list<VertexAttribute> vertex_attributes);

  void SetVertexData(void* data, uint32_t size);

  void SetIndexBuffer(uint32_t* indices, int32_t count);

  [[nodiscard]] int32_t GetCount() const;

 private:
  std::unique_ptr<IndexBuffer> index_buffer_;
  uint32_t renderer_id_{0};
  std::unique_ptr<VertexBuffer> vertex_buffer_;
};
}  // namespace qd::renderer
