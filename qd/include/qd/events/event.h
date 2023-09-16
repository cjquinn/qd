#pragma once

#define QD_EVENT_TYPE(type)                          \
  static Type getStaticType() { return Type::type; } \
  [[nodiscard]] inline Type GetType() const override { return getStaticType(); }

namespace qd::events {
enum class Type {
  kNone = 0,
  kKeyPressed,
  kKeyReleased,
  kMouseButtonPressed,
  kMouseButtonReleased,
  kMouseMoved,
  kWindowClosed,
  kWindowResized,
};

class Event {
 public:
  virtual ~Event() = default;

  [[nodiscard]] virtual Type GetType() const = 0;
  [[nodiscard]] inline bool GetIsHandled() const { return is_handled_; }
  inline void SetIsHandled(bool is_handled) { is_handled_ = is_handled; }

 private:
  bool is_handled_{false};
};

class Dispatcher {
 public:
  explicit Dispatcher(Event& event) : event_(event) {}

  template <class EventT, class CallableT>
  bool Dispatch(CallableT&& callback) {
    if (event_.GetType() == EventT::getStaticType()) {
      callback(static_cast<EventT&>(event_));
      return true;
    }
    return false;
  }

 private:
  Event& event_;
};
};  // namespace qd::events
