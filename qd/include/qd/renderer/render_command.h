#pragma once

#include <cstdint>
#include <glm/vec4.hpp>
#include <memory>

namespace qd::renderer {
class VertexArray;

namespace render_command {
void Init();

void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

void SetClearColor(const glm::vec4& color);

void Clear();

void Draw(const VertexArray& vertex_array, int32_t count = 0);
}  // namespace render_command
}  // namespace qd::renderer
