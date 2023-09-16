#pragma once

namespace qd::events {
class Event;
}

namespace qd::core {
class Layer {
 public:
  virtual ~Layer() = default;

  virtual void OnAttach();

  virtual void OnDetach();

  virtual void OnEvent(events::Event& event);

  virtual void Update();
};
}  // namespace qd::core
