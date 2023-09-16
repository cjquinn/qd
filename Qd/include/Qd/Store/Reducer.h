#pragma once

#include <functional>
#include <string>
#include <tuple>

namespace Qd {
template <class StateT, class ActionT>
using HandlerT = std::function<void(StateT &, const ActionT &)>;

template <class StateT, class... ReducersT>
class Reducer {
 public:
  explicit Reducer(const ReducersT &&...reducers) : reducers(reducers...) {}

  template <class ActionT>
  typename std::enable_if_t<
      (std::is_same_v<HandlerT<StateT, ActionT>, ReducersT> || ...), void>
  operator()(StateT &state, const ActionT &action) const {
    std::get<HandlerT<StateT, ActionT>>(reducers)(state, action);
  }

  template <class ActionT>
  typename std::enable_if_t<
      ((std::is_same_v<HandlerT<StateT, ActionT>, ReducersT> || ...) == false),
      void>
  operator()(StateT &state, const ActionT &action) const {
    return;
  }

  typedef StateT state_t;

 private:
  const std::tuple<ReducersT...> reducers;
};

template <typename StateT>
class ReducerFactory {
 public:
  template <class ActionT>
  static auto handler(HandlerT<StateT, ActionT> &&handler) {
    return handler;
  }

  template <typename... ReducersT>
  static auto make(ReducersT &&...reducers) {
    return Reducer<StateT, ReducersT...>(std::forward<ReducersT>(reducers)...);
  }
};
}  // namespace Qd
