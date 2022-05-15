#include "Core/Window.h"

#include "Qd/Core/Assert.h"
#include "Qd/Core/Log.h"
#include "Qd/Events/WindowEvent.h"

namespace Qd::Core {
    static void glfwErrorCallback(int error, const char* description) {
        QD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window::Window(const std::string& title, int width, int height) : data_{title, width, height} {
        int success = glfwInit();
        QD_CORE_ASSERT(success)

        glfwSetErrorCallback(glfwErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
        QD_CORE_ASSERT(window_)

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);

        QD_CORE_ASSERT(gladLoadGL());

        glfwSetWindowUserPointer(window_, &data_);

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
            Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            Events::WindowClosedEvent event{};
            data.eventCallback(event);
        });
    }

    Window::~Window() {
        if (!window_) {
            glfwDestroyWindow(window_);
        }
        glfwTerminate();
    }

    void Window::update() {
        glfwPollEvents();
        glfwSwapBuffers(window_);
    }

    void Window::setEventCallback(const EventCallbackT& eventCallback) {
        data_.eventCallback = eventCallback;
    }
}
