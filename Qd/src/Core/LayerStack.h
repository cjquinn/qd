#pragma once

#include <memory>
#include <vector>

namespace Qd::Core {
    class Layer;

    class LayerStack {
    public:
        ~LayerStack();

        void pushLayer(std::unique_ptr<Layer> layer);
        void pushOverlay(std::unique_ptr<Layer> overlay);

        inline std::vector<std::unique_ptr<Layer>>::iterator begin() { return layers_.begin(); }
        inline std::vector<std::unique_ptr<Layer>>::iterator end() { return layers_.end(); }
        inline std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() { return layers_.rbegin(); }
        inline std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() { return layers_.rend(); }

    private:
        std::vector<std::unique_ptr<Layer>> layers_;
        unsigned int layersTail_ = 0;
    };
}
