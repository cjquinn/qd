#pragma once

#include <Qd/Core/Layer.h>
#include <Qd/Renderer/Camera.h>
#include <Qd/Renderer/Shader.h>
#include <Qd/Renderer/Texture.h>
#include <Qd/Renderer/VertexArray.h>

namespace Qd::Events {
    class Event;
    class WindowResizedEvent;
}

namespace Sandbox {
    class SandboxLayer : public Qd::Core::Layer {
    public:
        void onAttach() override;

        void onDetach() override;

        void onEvent(Qd::Events::Event &event) override;

        void update() override;

    private:
        void handleWindowResized(Qd::Events::WindowResizedEvent &event);

    private:
        Qd::Renderer::Camera camera_{800.0f / 600.0f};
        Qd::Renderer::Shader shader_;
        Qd::Renderer::Texture texture_;
        Qd::Renderer::VertexArray vertexArray_;
    };
}
