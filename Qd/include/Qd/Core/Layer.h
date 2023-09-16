#pragma once

namespace Qd::Events {
class Event;
}

namespace Qd::Core {
class Layer {
 public:
  virtual ~Layer() = default;

  virtual void onAttach();

  virtual void onDetach();

  virtual void onEvent(Events::Event& event);

  virtual void update();
};
}  // namespace Qd::Core
