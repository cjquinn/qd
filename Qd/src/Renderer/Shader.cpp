#include "Qd/Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Qd/Core/Assert.h"
#include "Qd/Core/Log.h"

namespace {
GLuint compileShader(GLenum type, const std::string& source) {
    GLuint rendererId = glCreateShader(type);
    const GLchar *src = source.c_str();
    glShaderSource(rendererId, 1, &src, nullptr);
    glCompileShader(rendererId);

    GLint result;
    glGetShaderiv(rendererId, GL_COMPILE_STATUS, &result);
    if (result == GL_TRUE) {
        return rendererId;
    }

    GLint length;
    glGetShaderiv(rendererId, GL_INFO_LOG_LENGTH, &length);
    GLchar message[length];
    glGetShaderInfoLog(rendererId, length, &length, message);

    QD_CORE_CRITICAL("Failed to compile {} shader", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
    QD_CORE_CRITICAL(std::string_view{message});

    glDeleteShader(rendererId);

    QD_CORE_ASSERT(false);

    return 0;
}
}

namespace Qd::Renderer {
    void Shader::init(const std::string &vertexShader, const std::string &fragmentShader) {
        rendererId_ = glCreateProgram();
        GLuint vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
        GLuint fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(rendererId_, vertexShaderId);
        glAttachShader(rendererId_, fragmentShaderId);

        glLinkProgram(rendererId_);
        glValidateProgram(rendererId_);

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    Shader::~Shader() {
        glDeleteProgram(rendererId_);
    }

    void Shader::bind() const {
        QD_CORE_ASSERT(rendererId_);

        glUseProgram(rendererId_);
    }

    void Shader::setUniform1i(const std::string& name, int32_t value) const {
        GLint location = glGetUniformLocation(rendererId_, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::setUniformMat4(const std::string& name, const glm::mat4& value) const {
        GLint location = glGetUniformLocation(rendererId_, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
}
