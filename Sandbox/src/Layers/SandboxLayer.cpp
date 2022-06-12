#include "SandboxLayer.h"

#include <Qd/Events/Event.h>
#include <Qd/Renderer/RenderCommand.h>

namespace Sandbox {
    void SandboxLayer::onAttach() {
        shader_.init(
                R"(
                    #version 330 core

                    layout(location = 0) in vec2 a_Position;
                    layout(location = 1) in vec2 a_TexCoord;

                    out vec2 v_TexCoord;

                    void main()
                    {
                        gl_Position = vec4(a_Position, 0.0, 1.0);
                        v_TexCoord = a_TexCoord;
                    }
                )",
                R"(
                    #version 330 core

                    in vec2 v_TexCoord;

                    out vec4 color;

                    uniform sampler2D u_Texture;

                    void main()
                    {
                        color = texture(u_Texture, v_TexCoord);
                    }
                )"
        );

        texture_.init("assets/textures/alien.png");
        texture_.bind();
        shader_.setUniform1i("u_Texture", 0);

        vertexArray_.init();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 1.0f,// top left
                0.5f, -0.5f, 1.0f, 0.0f, // bottom right
                0.5f, 0.5f, 1.0f, 1.0f, // top right
        };

        vertexArray_.setVertexBuffer(vertices, sizeof(vertices), {
            {Qd::Renderer::ShaderType::Float, 2}, // position
            {Qd::Renderer::ShaderType::Float, 2}, // texture
        });

        uint32_t indices[] = {
                0, 1, 2,
                2, 1, 3,
        };
        vertexArray_.setIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));
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
