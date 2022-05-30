#include "Core/Window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Qd/Core/Assert.h"
#include "Qd/Core/Log.h"
#include "Qd/Events/KeyboardEvent.h"
#include "Qd/Events/MouseEvent.h"
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

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            auto keyCode = static_cast<KeyCode>(key);

            if (action == GLFW_RELEASE) {
                Events::KeyReleasedEvent event{keyCode};
                data.eventCallback(event);
                return;
            }

            Events::KeyPressedEvent event{keyCode, action == GLFW_REPEAT};
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
            Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            auto mouseCode = static_cast<MouseCode>(button);

            if (action == GLFW_RELEASE) {
                Events::MouseButtonReleasedEvent event{mouseCode};
                data.eventCallback(event);
                return;
            }

            Events::MouseButtonPressedEvent event{mouseCode};
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x, double y) {
            Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
            Events::MouseMovedEvent event{x, y};
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
