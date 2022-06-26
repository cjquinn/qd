#include "Qd/Renderer/RenderCommand.h"

#include <glad/glad.h>

#include "Qd/Core/Assert.h"
#include "Qd/Core/Log.h"
#include "Qd/Renderer/VertexArray.h"

namespace {
    void debugMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char* message,
            const void* userParam) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                QD_CORE_CRITICAL(message);
                return;

            case GL_DEBUG_SEVERITY_MEDIUM:
                QD_CORE_ERROR(message);
                return;

            case GL_DEBUG_SEVERITY_LOW:
                QD_CORE_WARN(message);
                return;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                QD_CORE_TRACE(message);
                return;

            default:
                QD_CORE_ASSERT(false, "Unknown severity level!");
                return;
        }
    }
}

namespace Qd::Renderer::RenderCommand {
    void init() {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void setViewport(int32_t x, int32_t y, int32_t width, int32_t height) {
        glViewport(x, y, width, height);
    }

    void setClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void draw(const VertexArray& vertexArray, int32_t count) {
        vertexArray.bind();
        glDrawElements(
                GL_TRIANGLES,
                count ? count : vertexArray.getCount(),
                GL_UNSIGNED_INT,
                nullptr
        );
    }
}
