#include "Qd/Application.h"

#include "Qd/Core/Base.h"

#include "Core/Window.h"

namespace Qd {
    Application::Application(const std::string& name) : window_(std::make_unique<Core::Window>(name, 800, 600)) {
        window_->setEventCallback(QD_BIND(Application::onEvent));
    }

    Application::~Application() = default;

    void Application::onEvent(Events::Event &event) {
        Events::Dispatcher dispatcher{event};

        dispatcher.dispatch<Events::WindowClosedEvent>(QD_BIND(Application::handleWindowClosed));
    }

    void Application::run() {
        while (isRunning_) {
            window_->update();
        }
    }

    void Application::handleWindowClosed(Events::WindowClosedEvent &event) {
        this->isRunning_ = false;
        event.setIsHandled(true);
    }
}
