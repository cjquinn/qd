#pragma once

#include <functional>

namespace Qd::Events {
    enum class EventType {
        None = 0,
        WindowClosed,
    };

    class Event {
    public:
        virtual ~Event() = default;

        [[nodiscard]] virtual EventType getEventType() const = 0;

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
            if (event_.getEventType() == EventT::getStaticEventType()) {
                callback(static_cast<EventT&>(event_));
                return true;
            }
            return false;
        }

    private:
        Event& event_;
    };
};
