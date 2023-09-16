#include "qd/renderer/render_command.h"

#include <glad/glad.h>

#include "qd/core/assert.h"
#include "qd/core/log.h"
#include "qd/renderer/vertex_array.h"

namespace {
void DebugMessageCallback(unsigned /*source*/, unsigned /*type*/,
                          unsigned /*id*/, unsigned severity, int /*length*/,
                          const char* message, const void* /*user_param*/) {
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
}  // namespace

namespace qd::renderer::render_command {
void Init() {
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(DebugMessageCallback, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}

void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) {
  glViewport(x, y, width, height);
}

void SetClearColor(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Draw(const VertexArray& vertex_array, int32_t count) {
  vertex_array.Bind();
  glDrawElements(GL_TRIANGLES, count ? count : vertex_array.GetCount(),
                 GL_UNSIGNED_INT, nullptr);
}
}  // namespace qd::renderer::render_command
