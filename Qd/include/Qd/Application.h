#pragma once

#include <memory>

#include "Qd/Events/Event.h"
#include "Qd/Events/WindowEvent.h"

namespace Qd::Core { class Window; }

extern int main();

namespace Qd {
    class Application {
    public:
        explicit Application(const std::string& name);
        virtual ~Application();

    private:
        bool isRunning_{true};
        std::unique_ptr<Core::Window> window_;

    private:
        friend int ::main();
        void run();
        void onEvent(Events::Event& event);
        void handleWindowClosed(Events::WindowClosedEvent& event);
    };
}
