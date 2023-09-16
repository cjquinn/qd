#pragma once

#include <functional>
#include <string>
#include <tuple>

namespace qd::store {
template <class StateT, class ActionT>
using HandlerT = std::function<void(StateT &, const ActionT &)>;

template <class StateT, class... ReducersT>
class Reducer {
 public:
  explicit Reducer(const ReducersT &&...reducers) : reducers_(reducers...) {}

  template <class ActionT>
  typename std::enable_if_t<
      (std::is_same_v<HandlerT<StateT, ActionT>, ReducersT> || ...), void>
  operator()(StateT &state, const ActionT &action) const {
    std::get<HandlerT<StateT, ActionT>>(reducers_)(state, action);
  }

  template <class ActionT>
  typename std::enable_if_t<
      (!static_cast<bool>(
          (std::is_same_v<HandlerT<StateT, ActionT>, ReducersT> || ...))),
      void>
  operator()(StateT &, const ActionT &) const {
    return;
  }

  using state_t = StateT;

 private:
  const std::tuple<ReducersT...> reducers_;
};

template <typename StateT>
class ReducerFactory {
 public:
  template <class ActionT>
  static auto Handler(HandlerT<StateT, ActionT> &&handler) {
    return handler;
  }

  template <typename... ReducersT>
  static auto Make(ReducersT &&...reducers) {
    return Reducer<StateT, ReducersT...>(std::forward<ReducersT>(reducers)...);
  }
};
}  // namespace qd::store
