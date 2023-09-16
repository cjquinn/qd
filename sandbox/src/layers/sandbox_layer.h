#pragma once

#include <qd/core/layer.h>
#include <qd/renderer/camera.h>
#include <qd/renderer/shader.h>
#include <qd/renderer/texture.h>
#include <qd/renderer/vertex_array.h>

namespace qd::events {
class Event;
class WindowResizedEvent;
}  // namespace qd::events

namespace sandbox {
class SandboxLayer : public qd::core::Layer {
 public:
  void OnAttach() override;

  void OnDetach() override;

  void OnEvent(qd::events::Event &event) override;

  void Update() override;

 private:
  void HandleWindowResized(qd::events::WindowResizedEvent &event);

  qd::renderer::Camera camera_{800.0F / 600.0F};
  qd::renderer::Shader shader_;
  qd::renderer::Texture texture_;
  qd::renderer::VertexArray vertex_array_;
};
}  // namespace sandbox
