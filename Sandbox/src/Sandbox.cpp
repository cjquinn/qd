#include <Qd/Application.h>
#include <Qd/EntryPoint.h>

#include <memory>

#include "Layers/BatchRendererLayer.h"

namespace Sandbox {
class Sandbox : public Qd::Application {
 public:
  Sandbox() : Application("Sandbox", 800, 600) {
    pushLayer(std::make_unique<BatchRendererLayer>());
  }

  ~Sandbox() override = default;
};
}  // namespace Sandbox

std::unique_ptr<Qd::Application> Qd::createApplication() {
  return std::make_unique<Sandbox::Sandbox>();
}
