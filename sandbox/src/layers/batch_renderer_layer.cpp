#include "batch_renderer_layer.h"

#include <qd/core/base.h>
#include <qd/events/event.h>
#include <qd/events/window_event.h>
#include <qd/renderer/render_command.h>

namespace sandbox {
void BatchRendererLayer::OnAttach() { renderer_.Init(); }

void BatchRendererLayer::OnDetach() {}

void BatchRendererLayer::OnEvent(qd::events::Event &event) {
  qd::events::Dispatcher dispatcher{event};

  dispatcher.Dispatch<qd::events::WindowResizedEvent>(
      QD_BIND(HandleWindowResized));
}

void BatchRendererLayer::Update() {
  qd::renderer::render_command::SetClearColor({0.1F, 0.1F, 0.1F, 1.0F});
  qd::renderer::render_command::Clear();

  renderer_.BeginScene(camera_);

  for (int x = -50; x < 50; x++) {
    for (int y = -50; y < 50; y++) {
      renderer_.DrawQuad({x * 0.11F, y * 0.11F}, {0.1F, 0.1F},
                         {1.0F, 1.0F, 1.0F, 1.0F});
    }
  }

  renderer_.EndScene();
}

void BatchRendererLayer::HandleWindowResized(
    qd::events::WindowResizedEvent &event) {
  camera_.SetProjection(static_cast<float>(event.GetWidth()) /
                        static_cast<float>(event.GetHeight()));
}
}  // namespace sandbox
