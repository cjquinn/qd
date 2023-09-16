#include "qd/renderer/renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "qd/renderer/camera.h"
#include "qd/renderer/render_command.h"

namespace qd::renderer {
void Renderer::Init() {
  shader_.Init(
      R"(
        #version 330 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;

        out vec4 v_Color;

        void main()
        {
          gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
          v_Color = a_Color;
        }
      )",
      R"(
        #version 330 core

        in vec4 v_Color;

        out vec4 color;

        void main()
        {
          color = v_Color;
        }
      )");

  vertex_array_.Init();

  vertex_array_.SetVertexBuffer(
      kMaxVertices * sizeof(Vertex),
      {
          {qd::renderer::ShaderType::kFloat, 2},  // position
          {qd::renderer::ShaderType::kFloat, 4},  // color
      });

  uint32_t indices[kMaxIndices]{};
  uint32_t offset{0};
  for (uint32_t i = 0; i < kMaxIndices; i += kQuadIndicies) {
    indices[i] = offset;
    indices[i + 1] = offset + 1;
    indices[i + 2] = offset + 2;

    indices[i + 3] = offset + 2;
    indices[i + 4] = offset + 3;
    indices[i + 5] = offset;

    offset += kQuadVertices;
  }
  vertex_array_.SetIndexBuffer(indices, kMaxIndices);
}

void Renderer::BeginScene(const Camera& camera) {
  shader_.Bind();
  shader_.SetUniformMat4("u_ViewProjection", camera.GetViewProjection());
}

void Renderer::EndScene() { Flush(); }

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& scale,
                        const glm::vec4& color) {
  static const glm::vec4 kQuadPositions[4] = {
      {-0.5F, -0.5F, 0.0F, 1.0F},  // Bottom left
      {0.5F, -0.5F, 0.0F, 1.0F},   // Bottom right
      {0.5F, 0.5F, 0.0F, 1.0F},    // Top right
      {-0.5F, 0.5F, 0.0F, 1.0F},   // Top left
  };

  if (indices_count_ >= kMaxIndices) {
    Flush();
  }

  glm::mat4 transform =
      glm::translate(glm::mat4{1.0F}, glm::vec3{position, 1.0F}) *
      glm::scale(glm::mat4{1.0F}, glm::vec3(scale, 1.0F));

  for (const auto& quad_position : kQuadPositions) {
    next_vertex_->position = transform * quad_position;
    next_vertex_->color = color;
    next_vertex_++;
  }

  indices_count_ += kQuadIndicies;
}

void Renderer::Flush() {
  if (indices_count_ > 0) {
    vertex_array_.SetVertexData(vertices_, sizeof(Vertex) * indices_count_ /
                                               kQuadIndicies * kQuadVertices);
    render_command::Draw(vertex_array_, indices_count_);
    next_vertex_ = vertices_;
    indices_count_ = 0;
  }
}
}  // namespace qd::renderer
