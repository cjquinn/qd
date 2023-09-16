#pragma once

#include <iostream>
#include <tuple>

namespace qd::store {
template <class ReducerT>
struct ReducerTrait {
  using state_t = typename ReducerT::state_t;
};

template <class... ReducersT>
class Store {
 public:
  using State = std::tuple<typename ReducerTrait<ReducersT>::state_t...>;

  explicit Store(const ReducersT&... reducers) : reducers_(reducers...) {}

  template <class StateT>
  [[nodiscard]] const StateT& GetState() const {
    return std::get<StateT>(state_);
  }

  template <class ActionT>
  void Dispatch(const ActionT& action) {
    apply(action, std::index_sequence_for<ReducersT...>{});
  }

 private:
  template <class ActionT, std::size_t... Is>
  void Apply(const ActionT& action, std::index_sequence<Is...>) {
    (std::get<Is>(reducers_)(std::get<Is>(state_), action), ...);
  }

  std::tuple<ReducersT...> reducers_;
  State state_;
};
}  // namespace qd::store
