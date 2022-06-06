#include "Qd/Renderer/VertexArray.h"

#include <unordered_map>

#include <glad/glad.h>

#include "Renderer/Buffer.h"

namespace {
GLenum getGlEnum(Qd::Renderer::ShaderType shaderType) {
    static const std::unordered_map<Qd::Renderer::ShaderType, GLenum> kShaderTypeToGLenum = {
            {Qd::Renderer::ShaderType::Float, GL_FLOAT}
    };
    return kShaderTypeToGLenum.at(shaderType);
}
}

namespace Qd::Renderer {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &rendererId_);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &rendererId_);
    }

    void VertexArray::bind() const {
        glBindVertexArray(rendererId_);
    }

    void VertexArray::setVertexBuffer(
            float* vertices,
            uint32_t size,
            std::initializer_list<VertexAttribute> vertexAttributes) {
        bind();
        vertexBuffer_.reset(new VertexBuffer{vertices, size});

        std::vector<VertexAttribute> layout{vertexAttributes};
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

    void VertexArray::setIndexBuffer(uint32_t* indices, int32_t count) {
        bind();
        indexBuffer_.reset(new IndexBuffer{indices, count});
    }

    int32_t VertexArray::getCount() const {
        if (indexBuffer_) {
            return indexBuffer_->getCount();
        }

        return 0;
    }
}
