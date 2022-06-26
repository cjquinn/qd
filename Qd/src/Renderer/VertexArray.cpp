#include "Qd/Renderer/VertexArray.h"

#include <unordered_map>

#include <glad/glad.h>

#include "Qd/Core/Assert.h"

#include "Renderer/Buffer.h"

namespace {
GLenum getGlEnum(Qd::Renderer::ShaderType shaderType) {
    static const std::unordered_map<Qd::Renderer::ShaderType, GLenum> kShaderTypeToGLenum = {
            {Qd::Renderer::ShaderType::Float, GL_FLOAT}
    };
    return kShaderTypeToGLenum.at(shaderType);
}

void setVertexLayout(std::initializer_list<Qd::Renderer::VertexAttribute> vertexAttributes) {
    std::vector<Qd::Renderer::VertexAttribute> layout{vertexAttributes};

    int32_t stride{0};
    for (auto& vertexAttribute : layout) {
        stride += vertexAttribute.count * static_cast<int32_t>(vertexAttribute.type);
        vertexAttribute.offset = stride;
    }

    uint32_t index{0};
    size_t offset{0};
    for (const auto& vertexAttribute : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            vertexAttribute.count,
            getGlEnum(vertexAttribute.type),
            vertexAttribute.isNormalized ? GL_TRUE : GL_FALSE,
            stride,
            (void*) offset
        );
        offset += vertexAttribute.offset;
        index++;
    }
}
}

namespace Qd::Renderer {
    VertexArray::VertexArray() = default;

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &rendererId_);
    }

    void VertexArray::init() {
        glGenVertexArrays(1, &rendererId_);
        glBindVertexArray(rendererId_);
    }

    void VertexArray::bind() const {
        QD_CORE_ASSERT(rendererId_);

        glBindVertexArray(rendererId_);
    }

    void VertexArray::setVertexBuffer(uint32_t size, std::initializer_list<VertexAttribute> vertexAttributes) {
        QD_CORE_ASSERT(rendererId_);

        vertexBuffer_.reset(new VertexBuffer{size});
        setVertexLayout(vertexAttributes);
    }

    void VertexArray::setVertexBuffer(
            float* vertices,
            uint32_t size,
            std::initializer_list<VertexAttribute> vertexAttributes) {
        QD_CORE_ASSERT(rendererId_);

        vertexBuffer_.reset(new VertexBuffer{vertices, size});
        setVertexLayout(vertexAttributes);
    }

    void VertexArray::setVertexData(void* data, uint32_t size) {
        vertexBuffer_->setData(data, size);
    }

    void VertexArray::setIndexBuffer(uint32_t* indices, int32_t count) {
        QD_CORE_ASSERT(rendererId_);

        indexBuffer_.reset(new IndexBuffer{indices, count});
    }

    int32_t VertexArray::getCount() const {
        if (indexBuffer_) {
            return indexBuffer_->getCount();
        }

        return 0;
    }
}
