#pragma once

#include "Qd/Events/Event.h"

namespace Qd::Events {
    class WindowClosedEvent : public Event {
    public:
        QD_EVENT_TYPE(WindowClosed)
    };
};
