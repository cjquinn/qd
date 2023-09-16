#pragma once

#include <cstdint>
#include <glm/vec4.hpp>
#include <memory>

namespace Qd::Renderer {
class VertexArray;

namespace RenderCommand {
void init();

void setViewport(int32_t x, int32_t y, int32_t width, int32_t height);

void setClearColor(const glm::vec4& color);

void clear();

void draw(const VertexArray& vertexArray, int32_t count = 0);
}  // namespace RenderCommand
}  // namespace Qd::Renderer
