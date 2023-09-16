#pragma once

#include "qd/events/event.h"

namespace qd::events {
class WindowClosedEvent : public Event {
 public:
  QD_EVENT_TYPE(kWindowClosed)
};

class WindowResizedEvent : public Event {
 public:
  explicit WindowResizedEvent(int width, int height)
      : width_(width), height_(height) {}

  QD_EVENT_TYPE(kWindowResized)

  [[nodiscard]] inline int GetWidth() const { return width_; }

  [[nodiscard]] inline int GetHeight() const { return height_; }

 private:
  int width_;
  int height_;
};
};  // namespace qd::events
