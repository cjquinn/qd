#pragma once

#include <string>

class GLFWwindow;

namespace qd::events {
class Event;
};

namespace qd::core {
class Window {
 public:
  using EventCallbackT = std::function<void(events::Event&)>;

  Window(const std::string& title, int width, int height);
  ~Window();

  void SetEventCallback(const EventCallbackT& event_callback);
  void Update();

 private:
  struct Data {
    std::string title;
    int width;
    int height;
    EventCallbackT event_callback;
  };

  Data data_;
  GLFWwindow* window_ = nullptr;
};
}  // namespace qd::core
