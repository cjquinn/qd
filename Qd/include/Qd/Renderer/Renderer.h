#pragma once

#include <Qd/Renderer/Shader.h>
#include <Qd/Renderer/VertexArray.h>

#include <cstdint>
#include <glm/glm.hpp>

constexpr int kMaxQuads = 1000;
constexpr int kQuadVertices = 4;
constexpr int kQuadIndicies = 6;
constexpr int kMaxVertices = kMaxQuads * kQuadVertices;
constexpr int kMaxIndices = kMaxQuads * kQuadIndicies;

namespace Qd::Renderer {
class Camera;

class Renderer {
 public:
  void init();

  void beginScene(const Camera& camera);
  void endScene();

  void drawQuad(const glm::vec2& position, const glm::vec2& scale,
                const glm::vec4& color);

 private:
  void flush();

 private:
  struct Vertex {
    glm::vec2 position;
    glm::vec4 color;
  };

  Shader shader_;

  VertexArray vertexArray_;
  Vertex vertices_[kMaxVertices]{};

  Vertex* nextVertex_{&vertices_[0]};
  int32_t indicesCount_{0};
};
}  // namespace Qd::Renderer
