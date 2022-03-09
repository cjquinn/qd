#pragma once

#include <functional>
#include <string>
#include <tuple>

#include "Qd/Store/Action.h"

namespace Qd {
    template <class State, class Action>
    struct ReducerFunction {
        using type = std::function<void(State&, const Action&)>;
    };

    template <class State, class ...Reducers>
    class Reducer {
    public:
        explicit Reducer(const Reducers &... reducers): reducers(reducers...) {}

        template <class Action>
        typename std::enable_if_t<(std::is_same_v<typename ReducerFunction<State, Action>::type, Reducers> || ...), void>
        operator()(State &state, const Action &action) const {
            std::get<typename ReducerFunction<State, Action>::type>(reducers)(state, action);
        }

        template <class Action>
        typename std::enable_if_t<((std::is_same_v<typename ReducerFunction<State, Action>::type, Reducers> || ...) == false), void>
        operator()(State &state, const Action &action) const {
            return;
        }

        typedef State state_t;

    private:
        const std::tuple<Reducers...> reducers;
    };

    template <class State>
    class ReducerFactory {
    public:
        template <class Action>
        auto& reducer(typename ReducerFunction<State, Action>::type &&reducer) {
            return reducer;
        }

        template <class ...Reducers>
        auto make(const Reducers &...reducers) {
            return Reducer<State, Reducers...>(reducers...);
        }
    };
}
