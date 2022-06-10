#include "SandboxLayer.h"

#include <Qd/Events/Event.h>
#include <Qd/Renderer/RenderCommand.h>

namespace Sandbox {
    void SandboxLayer::onAttach() {
        shader_.init(
                R"(
                    #version 330 core

                    layout(location = 0) in vec2 a_Position;
                    layout(location = 1) in vec3 a_Color;

                    out vec3 v_Color;

                    void main()
                    {
                        gl_Position = vec4(a_Position, 0.0, 1.0);
                        v_Color = a_Color;
                    }
                )",
                R"(
                    #version 330 core

                    in vec3 v_Color;

                    out vec4 color;

                    void main()
                    {
                        color = vec4(v_Color, 1.0);
                    }
                )"
        );

        vertexArray_.init();

        float vertices[] = {
                0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // top
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // right
                -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, // left
        };

        vertexArray_.setVertexBuffer(vertices, sizeof(vertices), {
            {Qd::Renderer::ShaderType::Float, 2}, // position
            {Qd::Renderer::ShaderType::Float, 3}, // color
        });

        uint32_t indices[] = {
                0, 1, 2,
        };
        vertexArray_.setIndexBuffer(indices, 3);
    }

    void SandboxLayer::onDetach() {

    }

    void SandboxLayer::onEvent(Qd::Events::Event &event) {

    }

    void SandboxLayer::update() {
        Qd::Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
        Qd::Renderer::RenderCommand::clear();

        shader_.bind();
        vertexArray_.bind();
        Qd::Renderer::RenderCommand::draw(vertexArray_);
    }
}
