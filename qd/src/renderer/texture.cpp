#include "qd/renderer/texture.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "qd/core/assert.h"

namespace qd::renderer {
void Texture::Init(const std::string& file) {
  int width{0};
  int height{0};
  int channels{0};

  stbi_set_flip_vertically_on_load(1);
  auto* buffer = stbi_load(file.c_str(), &width, &height, &channels, 0);

  QD_CORE_ASSERT(buffer);

  glGenTextures(1, &renderer_id_);
  glBindTexture(GL_TEXTURE_2D, renderer_id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  GLint internal_format{GL_RGBA8};
  GLenum data_format{GL_RGBA};
  if (channels == 3) {
    internal_format = GL_RGB8;
    data_format = GL_RGB;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format,
               GL_UNSIGNED_BYTE, buffer);

  glBindTexture(GL_TEXTURE_2D, 0);

  if (buffer) {
    stbi_image_free(buffer);
  }
}

Texture::~Texture() { glDeleteTextures(1, &renderer_id_); }

void Texture::Bind(uint32_t slot) const {
  QD_CORE_ASSERT(renderer_id_);
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, renderer_id_);
}
}  // namespace qd::renderer
