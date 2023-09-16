#pragma once

#include <iostream>
#include <tuple>

namespace Qd {
template <class ReducerT>
struct ReducerTrait {
  typedef typename ReducerT::state_t state_t;
};

template <class... ReducersT>
class Store {
 public:
  using State = std::tuple<typename ReducerTrait<ReducersT>::state_t...>;

  explicit Store(const ReducersT&... reducers) : reducers_(reducers...) {}

  template <class StateT>
  [[nodiscard]] const StateT& getState() const {
    return std::get<StateT>(state);
  }

  template <class ActionT>
  void dispatch(const ActionT& action) {
    apply(action, std::index_sequence_for<ReducersT...>{});
  }

 private:
  std::tuple<ReducersT...> reducers_;
  State state;

  template <class ActionT, std::size_t... Is>
  void apply(const ActionT& action, std::index_sequence<Is...>) {
    (std::get<Is>(reducers_)(std::get<Is>(state), action), ...);
  }
};
}  // namespace Qd
