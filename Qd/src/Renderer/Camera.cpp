#include "Qd/Renderer/Camera.h"

namespace Qd::Renderer {
    Camera::Camera(float aspectRatio) :
        aspectRatio_{aspectRatio},
        projection_{calculateProjection()},
        viewProjection_{calculateViewProjection()} {
    }

    void Camera::setPosition(const glm::vec3& position) {
        position_ = position;
        viewProjection_ = calculateViewProjection();
    }

    void Camera::setProjection(float aspectRatio) {
        aspectRatio_ = aspectRatio;
        projection_ = calculateProjection();
        viewProjection_ = calculateViewProjection();
    }

    void Camera::setZoom(float zoom) {
        zoom_ = zoom;
        projection_ = calculateProjection();
        viewProjection_ = calculateViewProjection();
    }

    glm::mat4 Camera::calculateProjection() const {
        return glm::ortho(-aspectRatio_ * zoom_, aspectRatio_ * zoom_, -zoom_, zoom_);
    }

    glm::mat4 Camera::calculateViewProjection() const {
        glm::mat4 transform = glm::translate(glm::mat4{1.0f}, position_);
        return projection_ * glm::inverse(transform);
    }
}
