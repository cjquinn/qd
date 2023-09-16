#pragma once

#include <cstdint>
#include <string>

namespace qd::renderer {
class Texture {
 public:
  ~Texture();

  void Init(const std::string& file);
  void Bind(uint32_t slot = 0) const;

 private:
  uint32_t renderer_id_{0};
};
}  // namespace qd::renderer
