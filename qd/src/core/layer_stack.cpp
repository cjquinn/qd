#include "layer_stack.h"

#include <utility>

#include "qd/core/layer.h"

namespace qd::core {
LayerStack::~LayerStack() {
  for (auto& layer : layers_) {
    layer->OnDetach();
  }
}

void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
  layers_.emplace(layers_.begin() + layers_tail_, std::move(layer));
  layers_tail_++;
}

void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay) {
  layers_.emplace_back(std::move(overlay));
}
}  // namespace qd::core
