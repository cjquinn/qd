#pragma once

#include <cstdint>

namespace Qd::Renderer {
    class VertexArray;

    class IndexBuffer {
    public:
        ~IndexBuffer();

    private:
        friend class VertexArray;

        explicit IndexBuffer(uint32_t* indices, int32_t count);

        [[nodiscard]] inline int32_t getCount() const {
            return count_;
        }

    private:
        int32_t count_{0};
        uint32_t rendererId_{0};
    };

    class VertexBuffer {
    public:
        ~VertexBuffer();

    private:
        friend class VertexArray;

        explicit VertexBuffer(float* vertices, uint32_t size);

    private:
        uint32_t rendererId_{0};
    };
}
