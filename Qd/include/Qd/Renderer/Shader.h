#pragma once

#include <cstdint>
#include <string>

namespace Qd::Renderer {
    class Shader {
    public:
        ~Shader();

        void init(const std::string& vertexShader, const std::string& fragmentShader);
        void bind() const;

    private:
        uint32_t rendererId_{0};
    };
}
