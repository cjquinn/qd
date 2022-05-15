#pragma once

#include "Event.h"

namespace Qd::Events {
    class WindowClosedEvent : public Event {
    public:
        WindowClosedEvent() = default;

        [[nodiscard]] inline EventType getEventType() const override {
            return EventType::WindowClosed;
        }

        static EventType getStaticEventType() {
            return EventType::WindowClosed;
        }
    };
};
