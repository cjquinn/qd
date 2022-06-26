#include <memory>

#include <Qd/Application.h>
#include <Qd/EntryPoint.h>

#include "Layers/BatchRendererLayer.h"
#include "Layers/SandboxLayer.h"

namespace Sandbox {
    class Sandbox : public Qd::Application {
    public:
        Sandbox() : Application("Sandbox", 800, 600) {
            pushLayer(std::make_unique<BatchRendererLayer>());
//            pushLayer(std::make_unique<SandboxLayer>());
        }

        ~Sandbox() override = default;
    };
}

std::unique_ptr<Qd::Application> Qd::createApplication() {
    return std::make_unique<Sandbox::Sandbox>();
}
