#pragma once

#include "Qd/Events/Event.h"

namespace Qd::Events {
class WindowClosedEvent : public Event {
 public:
  QD_EVENT_TYPE(WindowClosed)
};

class WindowResizedEvent : public Event {
 public:
  explicit WindowResizedEvent(int width, int height)
      : width_(width), height_(height) {}

  QD_EVENT_TYPE(WindowResized)

  [[nodiscard]] inline int getWidth() const { return width_; }

  [[nodiscard]] inline int getHeight() const { return height_; }

 private:
  int width_;
  int height_;
};
};  // namespace Qd::Events
