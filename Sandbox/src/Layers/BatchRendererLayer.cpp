#include "BatchRendererLayer.h"

#include <Qd/Core/Base.h>
#include <Qd/Events/Event.h>
#include <Qd/Events/WindowEvent.h>
#include <Qd/Renderer/RenderCommand.h>

namespace Sandbox {
void BatchRendererLayer::onAttach() { renderer_.init(); }

void BatchRendererLayer::onDetach() {}

void BatchRendererLayer::onEvent(Qd::Events::Event &event) {
  Qd::Events::Dispatcher dispatcher{event};

  dispatcher.dispatch<Qd::Events::WindowResizedEvent>(
      QD_BIND(handleWindowResized));
}

void BatchRendererLayer::update() {
  Qd::Renderer::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0});
  Qd::Renderer::RenderCommand::clear();

  renderer_.beginScene(camera_);

  for (int x = -50; x < 50; x++) {
    for (int y = -50; y < 50; y++) {
      renderer_.drawQuad({x * 0.11f, y * 0.11f}, {0.1f, 0.1f},
                         {1.0f, 1.0f, 1.0f, 1.0f});
    }
  }

  renderer_.endScene();
}

void BatchRendererLayer::handleWindowResized(
    Qd::Events::WindowResizedEvent &event) {
  camera_.setProjection(static_cast<float>(event.getWidth()) /
                        static_cast<float>(event.getHeight()));
}
}  // namespace Sandbox
