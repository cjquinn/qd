#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>

namespace Qd::Renderer {
    class Shader {
    public:
        ~Shader();

        void init(const std::string& vertexShader, const std::string& fragmentShader);
        void bind() const;

        void setUniform1i(const std::string& name, int32_t value) const;
        void setUniformMat4(const std::string& name, const glm::mat4 &value) const;

    private:
        uint32_t rendererId_{0};
    };
}
