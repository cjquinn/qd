#include <Qd/Core/Application.h>
#include <Qd/Core/Log.h>
#include <Qd/EntryPoint.h>
#include <Qd/Store/Action.h>
#include <Qd/Store/Reducer.h>
#include <Qd/Store/Store.h>

struct MovePlayerPayload {
    int x;
    int y;
};
struct MovePlayer : public Qd::Action<MovePlayerPayload> {};

struct Reset : public Qd::Action<bool> {};

struct KillPlayer : public Qd::Action<bool> {};

struct PlayerState {
    int x = 0;
    int y = 0;
    bool isAlive = true;
};

class Sandbox : public Qd::Application {
public:
    Sandbox() {
        Qd::ReducerFactory<PlayerState> playerReducerFactory;

        Qd::Store store(
            playerReducerFactory.make(
                playerReducerFactory.reducer<MovePlayer>([](auto &state, const auto &action) {
                    state.x = action.payload.x;
                    state.y = action.payload.y;
                }),
                playerReducerFactory.reducer<KillPlayer>([](auto &state, const auto &action) {
                    if (action.payload == true) {
                        state.isAlive = false;
                    }
                })
            )
        );

        auto& playerState = store.getState<PlayerState>();

        store.dispatch(MovePlayer{ 1, 2 });
        QD_INFO("Player state: x = {}, y = {}, isAlive = {}", playerState.x, playerState.y, playerState.isAlive);

        store.dispatch(MovePlayer{ 10, 20 });
        QD_INFO("Player state: x = {}, y = {}, isAlive = {}", playerState.x, playerState.y, playerState.isAlive);

        store.dispatch(Reset{ true });
        QD_INFO("Player state: x = {}, y = {}, isAlive = {}", playerState.x, playerState.y, playerState.isAlive);

        store.dispatch(KillPlayer{ true });
        QD_INFO("Player state: x = {}, y = {}, isAlive = {}", playerState.x, playerState.y, playerState.isAlive);
    }

    ~Sandbox() override = default;
};

Qd::Application* Qd::createApplication() {
    return new Sandbox();
}
