#pragma once

#include <memory>

extern int main();

namespace Qd {
    namespace Core {
        class Layer;
        class LayerStack;
        class Window;
    }

    namespace Events {
        class Event;
        class WindowClosedEvent;
    }

    class Application {
    public:
        explicit Application(const std::string& name, int width, int height);
        virtual ~Application();

        void pushLayer(std::unique_ptr<Core::Layer> layer);

        void pushOverlay(std::unique_ptr<Core::Layer> layer);

    private:
        bool isRunning_{true};
        std::unique_ptr<Core::LayerStack> layerStack_;
        std::unique_ptr<Core::Window> window_;

    private:
        friend int ::main();
        void handleWindowClosed(Events::WindowClosedEvent& event);
        void onEvent(Events::Event& event);
        void run();
    };
}
