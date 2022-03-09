#pragma once

#include <iostream>
#include <tuple>

namespace Qd {
    template <class Reducer>
    struct ReducerTrait {
        typedef typename Reducer::state_t state_t;
    };

    template <class ...Reducers>
    class Store {
    public:
        using State = std::tuple<typename ReducerTrait<Reducers>::state_t ...>;

        explicit Store(const Reducers &... reducers): reducers(reducers...) {}

        Store(const Store&) = delete;
        Store& operator=(const Store&) = delete;

        template <class State>
        [[nodiscard]] const State& getState() const {
            return std::get<State>(state);
        }

        template <class Action>
        void dispatch(const Action& action) {
            apply(action, std::index_sequence_for<Reducers...>{});
        }

    private:
        const std::tuple<Reducers...> reducers;
        State state;

        template <class Action, std::size_t... Is>
        void apply(const Action& action, std::index_sequence<Is...>) {
            (std::get<Is>(reducers)(std::get<Is>(state), action), ...);
        }
    };
}
