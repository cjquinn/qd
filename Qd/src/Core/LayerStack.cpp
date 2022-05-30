#include "Core/LayerStack.h"

#include <utility>

#include "Qd/Core/Layer.h"

namespace Qd::Core {
    LayerStack::~LayerStack() {
        for (auto& layer : layers_) {
            layer->onDetach();
        }
    }

    void LayerStack::pushLayer(std::unique_ptr<Layer> layer) {
        layers_.emplace(layers_.begin() + layersTail_, std::move(layer));
        layersTail_++;
    }

    void LayerStack::pushOverlay(std::unique_ptr<Layer> overlay) {
        layers_.emplace_back(std::move(overlay));
    }
}
