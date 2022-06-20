#include "SandboxLayer.h"

#include <Qd/Core/Base.h>
#include <Qd/Events/Event.h>
#include <Qd/Events/WindowEvent.h>
#include <Qd/Renderer/RenderCommand.h>

namespace Sandbox {
    void SandboxLayer::onAttach() {
        shader_.init(
                R"(
                    #version 330 core

                    layout(location = 0) in vec2 a_Position;
                    layout(location = 1) in vec2 a_TexCoord;

                    uniform mat4 u_ViewProjection;

                    out vec2 v_TexCoord;

                    void main()
                    {
                        gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
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

        texture_.init("assets/textures/aliens.png");
        texture_.bind();

        shader_.bind();
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
        Qd::Events::Dispatcher dispatcher{event};

        dispatcher.dispatch<Qd::Events::WindowResizedEvent>(QD_BIND(handleWindowResized));
    }

    void SandboxLayer::update() {
        Qd::Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
        Qd::Renderer::RenderCommand::clear();

        shader_.bind();
        shader_.setUniformMat4("u_ViewProjection", camera_.getViewProjection());
        vertexArray_.bind();
        Qd::Renderer::RenderCommand::draw(vertexArray_);
    }

    void SandboxLayer::handleWindowResized(Qd::Events::WindowResizedEvent &event) {
        camera_.setProjection(static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight()));
    }
}
