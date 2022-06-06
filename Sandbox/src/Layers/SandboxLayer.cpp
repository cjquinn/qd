#include "SandboxLayer.h"

#include <Qd/Events/Event.h>
#include <Qd/Renderer/RenderCommand.h>

namespace Sandbox {
    void SandboxLayer::onAttach() {
        float vertices[] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
        };
        vertexArray_.setVertexBuffer(vertices, 9, {
            {Qd::Renderer::ShaderType::Float, 3} // position
        });

        uint32_t indices[] = {
                0, 1, 2,
                2, 3, 0
        };
        vertexArray_.setIndexBuffer(indices, 6);
    }

    void SandboxLayer::onDetach() {

    }

    void SandboxLayer::onEvent(Qd::Events::Event &event) {

    }

    void SandboxLayer::update() {
        Qd::Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Qd::Renderer::RenderCommand::clear();
        Qd::Renderer::RenderCommand::draw(vertexArray_);
    }
}
