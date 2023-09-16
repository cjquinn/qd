#pragma once

#include <memory>

extern int main();

namespace qd {
namespace core {
class Layer;
class LayerStack;
class Window;
}  // namespace core

namespace events {
class Event;
class WindowClosedEvent;
}  // namespace events

class Application {
 public:
  explicit Application(const std::string& name, int width, int height);
  virtual ~Application();

  void PushLayer(std::unique_ptr<core::Layer> layer);

  void PushOverlay(std::unique_ptr<core::Layer> layer);

 private:
  friend int ::main();
  void HandleWindowClosed(events::WindowClosedEvent& event);
  void OnEvent(events::Event& event);
  void Run();

  bool isRunning_{true};
  std::unique_ptr<core::LayerStack> layer_stack_;
  std::unique_ptr<core::Window> window_;
};
}  // namespace qd
