#pragma once

#include <Qd/Core/Layer.h>
#include <Qd/Events/Event.h>

namespace Sandbox {
    class SandboxLayer : public Qd::Core::Layer {
        void onAttach() override;

        void onDetach() override;

        void onEvent(Qd::Events::Event &event) override;

        void update() override;
    };
}
