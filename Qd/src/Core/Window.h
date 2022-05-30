#pragma once

#include <string>

class GLFWwindow;

namespace Qd::Events { class Event; };

namespace Qd::Core {
    class Window {
    public:
        using EventCallbackT = std::function<void(Events::Event&)>;

        Window(const std::string& title, int width, int height);
        ~Window();

        void update();

        void setEventCallback(const EventCallbackT& eventCallback);

    private:
        GLFWwindow* window_ = nullptr;

        struct Data {
            std::string title;
            int width;
            int height;
            EventCallbackT eventCallback;
        };

        Data data_;
    };
}
