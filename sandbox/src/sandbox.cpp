#include <qd/application.h>
#include <qd/entry_point.h>

#include <memory>

#include "layers/batch_renderer_layer.h"

namespace sandbox {
class Sandbox : public qd::Application {
 public:
  Sandbox() : Application("Sandbox", 800, 600) {
    PushLayer(std::make_unique<BatchRendererLayer>());
  }

  ~Sandbox() override = default;
};
}  // namespace sandbox

std::unique_ptr<qd::Application> qd::CreateApplication() {
  return std::make_unique<sandbox::Sandbox>();
}
