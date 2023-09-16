#pragma once

#include <Qd/Core/Layer.h>
#include <Qd/Renderer/Camera.h>
#include <Qd/Renderer/Renderer.h>

namespace Qd::Events {
class Event;
class WindowResizedEvent;
}  // namespace Qd::Events

namespace Sandbox {
class BatchRendererLayer : public Qd::Core::Layer {
 public:
  void onAttach() override;

  void onDetach() override;

  void onEvent(Qd::Events::Event &event) override;

  void update() override;

 private:
  void handleWindowResized(Qd::Events::WindowResizedEvent &event);

 private:
  Qd::Renderer::Camera camera_{800.0f / 600.0f};
  Qd::Renderer::Renderer renderer_;
};
}  // namespace Sandbox
