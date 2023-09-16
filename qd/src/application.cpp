#include "qd/application.h"

#include <ranges>
#include <utility>

#include "core/layer_stack.h"
#include "core/window.h"
#include "qd/core/base.h"
#include "qd/core/layer.h"
#include "qd/events/event.h"
#include "qd/events/window_event.h"
#include "qd/renderer/render_command.h"

namespace {
void HandleWindowResized(qd::events::WindowResizedEvent &event) {
  qd::renderer::render_command::SetViewport(0, 0, event.GetWidth(),
                                            event.GetHeight());
}
}  // namespace

namespace qd {
Application::Application(const std::string &name, int width, int height)
    : layer_stack_{std::make_unique<core::LayerStack>()},
      window_{std::make_unique<core::Window>(name, width, height)} {
  window_->SetEventCallback(QD_BIND(OnEvent));
}

Application::~Application() = default;

void Application::PushLayer(std::unique_ptr<core::Layer> layer) {
  layer->OnAttach();
  layer_stack_->PushLayer(std::move(layer));
}

void Application::PushOverlay(std::unique_ptr<core::Layer> layer) {
  layer->OnAttach();
  layer_stack_->PushOverlay(std::move(layer));
}

void Application::HandleWindowClosed(events::WindowClosedEvent &event) {
  isRunning_ = false;
  event.SetIsHandled(true);
}

void Application::OnEvent(events::Event &event) {
  events::Dispatcher dispatcher{event};

  dispatcher.Dispatch<events::WindowClosedEvent>(QD_BIND(HandleWindowClosed));
  dispatcher.Dispatch<events::WindowResizedEvent>(HandleWindowResized);

  for (auto &it : std::ranges::reverse_view(*layer_stack_)) {
    if (event.GetIsHandled()) {
      break;
    }

    it->OnEvent(event);
  }
}

void Application::Run() {
  while (isRunning_) {
    for (auto &layer : *layer_stack_) {
      layer->Update();
    }

    window_->Update();
  }
}
}  // namespace qd
