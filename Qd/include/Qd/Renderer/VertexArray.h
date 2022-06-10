#pragma once

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

namespace Qd::Renderer {
    class IndexBuffer;
    class VertexBuffer;

    enum class ShaderType : uint32_t {
        Float = 4,
    };

    struct VertexAttribute {
        VertexAttribute(ShaderType type, int32_t count, bool isNormalized = false)
        : count{count}, isNormalized{isNormalized}, type{type} {}

        ShaderType type;
        int32_t count;
        bool isNormalized;
        size_t offset{0};
    };

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void init();
        void bind() const;

        void setVertexBuffer(float* vertices, uint32_t size, std::initializer_list<VertexAttribute> vertexAttributes);
        void setIndexBuffer(uint32_t* indices, int32_t count);

        [[nodiscard]] int32_t getCount() const;

    private:
        std::unique_ptr<IndexBuffer> indexBuffer_;
        uint32_t rendererId_{0};
        std::unique_ptr<VertexBuffer> vertexBuffer_;
    };
}
