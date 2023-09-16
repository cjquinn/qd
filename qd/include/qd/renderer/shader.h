#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>

namespace qd::renderer {
class Shader {
 public:
  ~Shader();

  void Init(const std::string& vertex_shader,
            const std::string& fragment_shader);
  void Bind() const;

  void SetUniform1i(const std::string& name, int32_t value) const;
  void SetUniformMat4(const std::string& name, const glm::mat4& value) const;

 private:
  uint32_t rendererId_{0};
};
}  // namespace qd::renderer
