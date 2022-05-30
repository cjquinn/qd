#pragma once

#include "Qd/Core/Codes.h"
#include "Qd/Events/Event.h"

namespace {
    class KeyboardEvent : public Qd::Events::Event {
    public:
        [[nodiscard]] inline Qd::Core::KeyCode getKeyCode() const {
            return keyCode_;
        }

    protected:
        explicit KeyboardEvent(Qd::Core::KeyCode keyCode) : keyCode_(keyCode) {}

        Qd::Core::KeyCode keyCode_;
    };
}

namespace Qd::Events {
    class KeyPressedEvent : public KeyboardEvent {
    public:
        explicit KeyPressedEvent(Core::KeyCode keyCode, bool isRepeat) : KeyboardEvent(keyCode), isRepeat_(isRepeat) {}

        [[nodiscard]] inline bool getIsRepeat() const {
            return isRepeat_;
        }

        QD_EVENT_TYPE(KeyPressed)

    private:
        bool isRepeat_{};
    };

    class KeyReleasedEvent : public KeyboardEvent {
    public:
        explicit KeyReleasedEvent(Core::KeyCode keyCode) : KeyboardEvent(keyCode) {}

        QD_EVENT_TYPE(KeyReleased)
    };
};
