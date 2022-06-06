#pragma once

#include "Qd/Core/Codes.h"
#include "Qd/Events/Event.h"

namespace {
    class MouseButtonEvent : public Qd::Events::Event {
    public:
        [[nodiscard]] inline Qd::Core::MouseCode getKeyCode() const {
            return mouseCode_;
        }

        protected:
        explicit MouseButtonEvent(Qd::Core::MouseCode mouseCode) : mouseCode_(mouseCode) {}

        Qd::Core::MouseCode mouseCode_;
    };
}

namespace Qd::Events {
    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(Core::MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

        QD_EVENT_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(Core::MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

        QD_EVENT_TYPE(MouseButtonReleased)
    };

    class MouseMovedEvent : public Event {
    public:
        explicit MouseMovedEvent(double x, double y) : x_(x), y_(y) {}

        QD_EVENT_TYPE(MouseMoved)

        [[nodiscard]] inline double getX() const {
            return x_;
        }

        [[nodiscard]] inline double getY() const {
            return y_;
        }

    private:
        double x_;
        double y_;
    };
}
