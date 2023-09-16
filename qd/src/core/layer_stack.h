#pragma once

#include <memory>
#include <vector>

namespace qd::core {
class Layer;

class LayerStack {
 public:
  ~LayerStack();

  void PushLayer(std::unique_ptr<Layer> layer);
  void PushOverlay(std::unique_ptr<Layer> overlay);

  // NOLINTNEXTLINE
  inline std::vector<std::unique_ptr<Layer>>::iterator begin() {
    return layers_.begin();
  }

  // NOLINTNEXTLINE
  inline std::vector<std::unique_ptr<Layer>>::iterator end() {
    return layers_.end();
  }

  // NOLINTNEXTLINE
  inline std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin() {
    return layers_.rbegin();
  }

  // NOLINTNEXTLINE
  inline std::vector<std::unique_ptr<Layer>>::reverse_iterator rend() {
    return layers_.rend();
  }

 private:
  std::vector<std::unique_ptr<Layer>> layers_;
  unsigned int layers_tail_ = 0;
};
}  // namespace qd::core
