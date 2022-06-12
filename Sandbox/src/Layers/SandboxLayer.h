#pragma once

#include <Qd/Core/Layer.h>
#include <Qd/Renderer/Shader.h>
#include <Qd/Renderer/Texture.h>
#include <Qd/Renderer/VertexArray.h>

namespace Qd::Events {
    class Event;
}

namespace Sandbox {
    class SandboxLayer : public Qd::Core::Layer {
    public:
        void onAttach() override;

        void onDetach() override;

        void onEvent(Qd::Events::Event &event) override;

        void update() override;

    private:
        Qd::Renderer::Shader shader_;
        Qd::Renderer::Texture texture_;
        Qd::Renderer::VertexArray vertexArray_;
    };
}
