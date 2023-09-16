#pragma once

#include <qd/core/layer.h>
#include <qd/renderer/camera.h>
#include <qd/renderer/renderer.h>

namespace qd::events {
class Event;
class WindowResizedEvent;
}  // namespace qd::events

namespace sandbox {
class BatchRendererLayer : public qd::core::Layer {
 public:
  void OnAttach() override;

  void OnDetach() override;

  void OnEvent(qd::events::Event &event) override;

  void Update() override;

 private:
  void HandleWindowResized(qd::events::WindowResizedEvent &event);

  qd::renderer::Camera camera_{800.0F / 600.0F};
  qd::renderer::Renderer renderer_;
};
}  // namespace sandbox
