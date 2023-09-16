#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace qd::renderer {
class Camera {
 public:
  explicit Camera(float aspect_ratio);

  void SetPosition(const glm::vec3& position);
  void SetProjection(float aspect_ratio);
  void SetZoom(float zoom);

  [[nodiscard]] inline const glm::mat4& GetViewProjection() const {
    return view_projection_;
  }

 private:
  [[nodiscard]] glm::mat4 CalculateProjection() const;
  [[nodiscard]] glm::mat4 CalculateViewProjection() const;

  glm::vec3 position_{0.0F, 0.0F, 0.0F};
  float zoom_{1.0F};
  float aspect_ratio_;
  glm::mat4 projection_;
  glm::mat4 view_projection_;
};
}  // namespace qd::renderer
