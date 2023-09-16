#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "qd/renderer/shader.h"
#include "qd/renderer/vertex_array.h"

constexpr int kMaxQuads = 1000;
constexpr int kQuadVertices = 4;
constexpr int kQuadIndicies = 6;
constexpr int kMaxVertices = kMaxQuads * kQuadVertices;
constexpr int kMaxIndices = kMaxQuads * kQuadIndicies;

namespace qd::renderer {
class Camera;

class Renderer {
 public:
  void Init();

  void BeginScene(const Camera& camera);
  void EndScene();

  void DrawQuad(const glm::vec2& position, const glm::vec2& scale,
                const glm::vec4& color);

 private:
  void Flush();
  struct Vertex {
    glm::vec2 position;
    glm::vec4 color;
  };

  Shader shader_;

  VertexArray vertex_array_;
  Vertex vertices_[kMaxVertices]{};

  Vertex* next_vertex_{&vertices_[0]};
  int32_t indices_count_{0};
};
}  // namespace qd::renderer
