#pragma once

#include <cstdint>
#include <string>

namespace Qd::Renderer {
class Texture {
 public:
  ~Texture();

  void init(const std::string& file);
  void bind(uint32_t slot = 0) const;

 private:
  uint32_t rendererId_{0};
};
}  // namespace Qd::Renderer
