#pragma once

#include <cstdint>

namespace qd::renderer {
class VertexArray;

class IndexBuffer {
 public:
  ~IndexBuffer();

 private:
  friend class VertexArray;

  explicit IndexBuffer(uint32_t* indices, int32_t count);
  [[nodiscard]] inline int32_t GetCount() const { return count_; }

  int32_t count_{0};
  uint32_t renderer_id_{0};
};

class VertexBuffer {
 public:
  ~VertexBuffer();

  void SetData(void* data, uint32_t size) const;

 private:
  friend class VertexArray;

  explicit VertexBuffer(uint32_t size);
  explicit VertexBuffer(float* vertices, uint32_t size);

  uint32_t renderer_id_{0};
};
}  // namespace qd::renderer
