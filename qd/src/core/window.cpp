#include "window.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "qd/core/assert.h"
#include "qd/core/log.h"
#include "qd/events/keyboard_event.h"
#include "qd/events/mouse_event.h"
#include "qd/events/window_event.h"

namespace {
void GlfwErrorCallback(int error, const char* description) {
  QD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}
}  // namespace

namespace qd::core {
Window::Window(const std::string& title, int width, int height)
    : data_{title, width, height} {
  int success = glfwInit();
  QD_CORE_ASSERT(success)

  glfwSetErrorCallback(GlfwErrorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(),
                             nullptr, nullptr);
  QD_CORE_ASSERT(window_)

  glfwMakeContextCurrent(window_);
  glfwSwapInterval(1);

  QD_CORE_ASSERT(gladLoadGL());

  glfwSetWindowUserPointer(window_, &data_);

  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int /*scancode*/,
                                 int action, int /*mods*/) {
    Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
    auto key_code = static_cast<KeyCode>(key);

    if (action == GLFW_RELEASE) {
      events::KeyReleasedEvent event{key_code};
      data.event_callback(event);
      return;
    }

    events::KeyPressedEvent event{key_code, action == GLFW_REPEAT};
    data.event_callback(event);
  });

  glfwSetMouseButtonCallback(
      window_, [](GLFWwindow* window, int button, int action, int /*mods*/) {
        Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
        auto mouse_code = static_cast<MouseCode>(button);

        if (action == GLFW_RELEASE) {
          events::MouseButtonReleasedEvent event{mouse_code};
          data.event_callback(event);
          return;
        }

        events::MouseButtonPressedEvent event{mouse_code};
        data.event_callback(event);
      });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x, double y) {
    Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
    events::MouseMovedEvent event{x, y};
    data.event_callback(event);
  });

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
    Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
    events::WindowClosedEvent event{};
    data.event_callback(event);
  });

  glfwSetWindowSizeCallback(
      window_, [](GLFWwindow* window, int width, int height) {
        Data& data = *static_cast<Data*>(glfwGetWindowUserPointer(window));
        events::WindowResizedEvent event{width, height};
        data.event_callback(event);
      });
}

Window::~Window() {
  if (!window_) {
    glfwDestroyWindow(window_);
  }
  glfwTerminate();
}

void Window::SetEventCallback(const EventCallbackT& event_callback) {
  data_.event_callback = event_callback;
}

void Window::Update() {
  glfwPollEvents();
  glfwSwapBuffers(window_);
}
}  // namespace qd::core
