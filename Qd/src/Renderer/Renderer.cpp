#include "Qd/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Qd/Renderer/Camera.h"
#include "Qd/Renderer/RenderCommand.h"

namespace Qd::Renderer {
    void Renderer::init() {
        shader_.init(
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
                )"
        );

        vertexArray_.init();

        vertexArray_.setVertexBuffer(kMaxVertices * sizeof(Vertex), {
            {Qd::Renderer::ShaderType::Float, 2}, // position
            {Qd::Renderer::ShaderType::Float, 4}, // color
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
        vertexArray_.setIndexBuffer(indices, kMaxIndices);
    }

    void Renderer::beginScene(const Camera &camera) {
        shader_.bind();
        shader_.setUniformMat4("u_ViewProjection", camera.getViewProjection());
    }

    void Renderer::endScene() {
        flush();
    }

    void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4 &color) {
        static const glm::vec4 quadPositions[4] = {
        {-0.5f, -0.5f, 0.0f, 1.0f}, // Bottom left
        {0.5f,  -0.5f, 0.0f, 1.0f}, // Bottom right
        {0.5f,  0.5f, 0.0f, 1.0f}, // Top right
        {-0.5f, 0.5f, 0.0f, 1.0f}, // Top left
        };

        if (indicesCount_ >= kMaxIndices) {
            flush();
        }

        glm::mat4 transform = glm::translate(glm::mat4{1.0f}, glm::vec3{position, 1.0f})
            * glm::scale(glm::mat4{1.0f}, glm::vec3(scale, 1.0f));

        for (auto& quadPosition : quadPositions) {
            nextVertex_->position = transform * quadPosition;
            nextVertex_->color = color;
            nextVertex_++;
        }

        indicesCount_ += kQuadIndicies;
    }

    void Renderer::flush() {
        if (indicesCount_ > 0) {
            vertexArray_.setVertexData(
            vertices_,
            sizeof(Vertex) * indicesCount_ / kQuadIndicies * kQuadVertices
            );
            RenderCommand::draw(vertexArray_, indicesCount_);
            nextVertex_ = vertices_;
            indicesCount_ = 0;
        }
    }
}
