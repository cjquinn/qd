#include "Qd/Application.h"

#include <utility>

#include "Qd/Core/Base.h"
#include "Qd/Core/Layer.h"
#include "Qd/Events/Event.h"
#include "Qd/Events/WindowEvent.h"
#include "Qd/Renderer/RenderCommand.h"

#include "Core/LayerStack.h"
#include "Core/Window.h"

namespace {
    void handleWindowResized(Qd::Events::WindowResizedEvent &event) {
        Qd::Renderer::RenderCommand::setViewport(0, 0, event.getWidth(), event.getHeight());
    }
}

namespace Qd {
    Application::Application(const std::string& name, int width, int height)
        : layerStack_{std::make_unique<Core::LayerStack>()},
          window_{std::make_unique<Core::Window>(name, width, height)} {
        window_->setEventCallback(QD_BIND(onEvent));
    }

    Application::~Application() = default;

    void Application::pushLayer(std::unique_ptr<Core::Layer> layer) {
        layer->onAttach();
        layerStack_->pushLayer(std::move(layer));
    }

    void Application::pushOverlay(std::unique_ptr<Core::Layer> layer) {
        layer->onAttach();
        layerStack_->pushOverlay(std::move(layer));
    }

    void Application::handleWindowClosed(Events::WindowClosedEvent &event) {
        isRunning_ = false;
        event.setIsHandled(true);
    }

    void Application::onEvent(Events::Event &event) {
        Events::Dispatcher dispatcher{event};

        dispatcher.dispatch<Events::WindowClosedEvent>(QD_BIND(handleWindowClosed));
        dispatcher.dispatch<Events::WindowResizedEvent>(handleWindowResized);

        for (auto it = layerStack_->rbegin(); it != layerStack_->rend(); ++it) {
            if (event.getIsHandled()) {
                break;
            }

            (*it)->onEvent(event);
        }
    }

    void Application::run() {
        while (isRunning_) {
            for (auto& layer : *layerStack_) {
                layer->update();
            }

            window_->update();
        }
    }
}
