#pragma once

#include "qd/core/codes.h"
#include "qd/events/event.h"

namespace qd::events {
class KeyboardEvent : public Event {
 public:
  [[nodiscard]] inline core::KeyCode GetKeyCode() const { return keyCode_; }

 protected:
  explicit KeyboardEvent(core::KeyCode key_code) : keyCode_(key_code) {}

  qd::core::KeyCode keyCode_;
};

class KeyPressedEvent : public KeyboardEvent {
 public:
  explicit KeyPressedEvent(core::KeyCode key_code, bool is_repeat)
      : KeyboardEvent(key_code), is_repeat_(is_repeat) {}

  [[nodiscard]] inline bool GetIsRepeat() const { return is_repeat_; }

  QD_EVENT_TYPE(kKeyPressed)

 private:
  bool is_repeat_{};
};

class KeyReleasedEvent : public KeyboardEvent {
 public:
  explicit KeyReleasedEvent(core::KeyCode key_code) : KeyboardEvent(key_code) {}

  QD_EVENT_TYPE(kKeyReleased)
};
};  // namespace qd::events
