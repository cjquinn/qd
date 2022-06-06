#pragma once

#define QD_EVENT_TYPE(type) static Type getStaticType() { return Type::type; } \
    [[nodiscard]] inline Type getType() const override { return getStaticType(); }

namespace Qd::Events {
    enum class Type {
        None = 0,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        WindowClosed,
        WindowResized,
    };

    class Event {
    public:
        virtual ~Event() = default;

        [[nodiscard]] virtual Type getType() const = 0;

        [[nodiscard]] inline bool getIsHandled() const {
            return isHandled_;
        }

        inline void setIsHandled(bool isHandled) {
            isHandled_ = isHandled;
        }

    private:
        bool isHandled_{false};
    };

    class Dispatcher {
    public:
        explicit Dispatcher(Event& event): event_(event) {}

        template <class EventT, class CallableT>
        bool dispatch(CallableT&& callback) {
            if (event_.getType() == EventT::getStaticType()) {
                callback(static_cast<EventT&>(event_));
                return true;
            }
            return false;
        }

    private:
        Event& event_;
    };
};
