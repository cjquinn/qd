#include "qd/renderer/camera.h"

namespace qd::renderer {
Camera::Camera(float aspect_ratio)
    : aspect_ratio_{aspect_ratio},
      projection_{CalculateProjection()},
      view_projection_{CalculateViewProjection()} {}

void Camera::SetPosition(const glm::vec3& position) {
  position_ = position;
  view_projection_ = CalculateViewProjection();
}

void Camera::SetProjection(float aspect_ratio) {
  aspect_ratio = aspect_ratio;
  projection_ = CalculateProjection();
  view_projection_ = CalculateViewProjection();
}

void Camera::SetZoom(float zoom) {
  zoom_ = zoom;
  projection_ = CalculateProjection();
  view_projection_ = CalculateViewProjection();
}

glm::mat4 Camera::CalculateProjection() const {
  return glm::ortho(-aspect_ratio_ * zoom_, aspect_ratio_ * zoom_, -zoom_,
                    zoom_);
}

glm::mat4 Camera::CalculateViewProjection() const {
  glm::mat4 transform = glm::translate(glm::mat4{1.0F}, position_);
  return projection_ * glm::inverse(transform);
}
}  // namespace qd::renderer
