#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace Qd::Renderer {
    class Camera {
    public:
        explicit Camera(float aspectRatio);

        void setPosition(const glm::vec3& position);
        void setProjection(float aspectRatio);
        void setZoom(float zoom);

        [[nodiscard]] inline const glm::mat4& getViewProjection() const {
            return viewProjection_;
        }

    private:
        [[nodiscard]] glm::mat4 calculateProjection() const;
        [[nodiscard]] glm::mat4 calculateViewProjection() const;

    private:
        glm::vec3 position_{0.0f, 0.0f, 0.0f};
        float zoom_{1.0f};
        float aspectRatio_;
        glm::mat4 projection_;
        glm::mat4 viewProjection_;
    };
}
