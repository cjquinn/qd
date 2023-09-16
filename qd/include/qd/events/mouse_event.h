#pragma once

#include "qd/core/codes.h"
#include "qd/events/event.h"

namespace qd::events {
class MouseButtonEvent : public Event {
 public:
  [[nodiscard]] inline core::MouseCode GetKeyCode() const {
    return mouse_code_;
  }

 protected:
  explicit MouseButtonEvent(core::MouseCode mouse_code)
      : mouse_code_(mouse_code) {}

  core::MouseCode mouse_code_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonPressedEvent(core::MouseCode mouse_code)
      : MouseButtonEvent(mouse_code) {}

  QD_EVENT_TYPE(kMouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  explicit MouseButtonReleasedEvent(core::MouseCode mouse_code)
      : MouseButtonEvent(mouse_code) {}

  QD_EVENT_TYPE(kMouseButtonReleased)
};

class MouseMovedEvent : public Event {
 public:
  explicit MouseMovedEvent(double x, double y) : x_(x), y_(y) {}

  QD_EVENT_TYPE(kMouseMoved)

  [[nodiscard]] inline double GetX() const { return x_; }

  [[nodiscard]] inline double GetY() const { return y_; }

 private:
  double x_;
  double y_;
};
}  // namespace qd::events
