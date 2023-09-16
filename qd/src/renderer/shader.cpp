#include "qd/renderer/shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "qd/core/assert.h"
#include "qd/core/log.h"

namespace {
GLuint CompileShader(GLenum type, const std::string& source) {
  GLuint renderer_id = glCreateShader(type);
  const GLchar* src = source.c_str();
  glShaderSource(renderer_id, 1, &src, nullptr);
  glCompileShader(renderer_id);

  GLint result;
  glGetShaderiv(renderer_id, GL_COMPILE_STATUS, &result);
  if (result == GL_TRUE) {
    return renderer_id;
  }

  GLint length;
  glGetShaderiv(renderer_id, GL_INFO_LOG_LENGTH, &length);
  GLchar message[length];
  glGetShaderInfoLog(renderer_id, length, &length, message);

  QD_CORE_CRITICAL("Failed to compile {} shader",
                   type == GL_VERTEX_SHADER ? "vertex" : "fragment");
  QD_CORE_CRITICAL(std::string_view{message});

  glDeleteShader(renderer_id);

  QD_CORE_ASSERT(false);

  return 0;
}
}  // namespace

namespace qd::renderer {
void Shader::Init(const std::string& vertex_shader,
                  const std::string& fragment_shader) {
  rendererId_ = glCreateProgram();
  GLuint vertex_shader_id = CompileShader(GL_VERTEX_SHADER, vertex_shader);
  GLuint fragment_shader_id =
      CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(rendererId_, vertex_shader_id);
  glAttachShader(rendererId_, fragment_shader_id);

  glLinkProgram(rendererId_);
  glValidateProgram(rendererId_);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);
}

Shader::~Shader() { glDeleteProgram(rendererId_); }

void Shader::Bind() const {
  QD_CORE_ASSERT(rendererId_);

  glUseProgram(rendererId_);
}

void Shader::SetUniform1i(const std::string& name, int32_t value) const {
  GLint location = glGetUniformLocation(rendererId_, name.c_str());
  glUniform1i(location, value);
}

void Shader::SetUniformMat4(const std::string& name,
                            const glm::mat4& value) const {
  GLint location = glGetUniformLocation(rendererId_, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
}  // namespace qd::renderer
