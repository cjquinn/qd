#pragma once

#include <cstdint>
#include <memory>

#include <glm/vec4.hpp>

namespace Qd::Renderer {
    class VertexArray;

    class RenderCommand {
    public:
        static void init();

        static void setViewport(int32_t x, int32_t y, int32_t width, int32_t height);

        static void setClearColor(const glm::vec4& color);

        static void clear();

        static void draw(const VertexArray& vertexArray, int32_t count = 0);
    };
}
