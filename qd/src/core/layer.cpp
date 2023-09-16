#include "qd/core/layer.h"

#include "qd/events/event.h"

namespace qd::core {
void Layer::OnAttach() {}

void Layer::OnDetach() {}

void Layer::OnEvent(events::Event &event) {}

void Layer::Update() {}
}  // namespace qd::core
