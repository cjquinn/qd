#include "Qd/Renderer/Texture.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Qd/Core/Assert.h"

namespace Qd::Renderer {
    void Texture::init(const std::string& file) {
        int width{0};
        int height{0};
        int channels{0};

        stbi_set_flip_vertically_on_load(true);
        auto buffer = stbi_load(file.c_str(),&width,&height,&channels,4);

        QD_CORE_ASSERT(buffer);

        glGenTextures(1, &rendererId_);
        glBindTexture(GL_TEXTURE_2D, rendererId_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);

        if (buffer) {
            stbi_image_free(buffer);
        }
    }

    Texture::~Texture() {
        glDeleteTextures(1, &rendererId_);
    }

    void Texture::bind(uint32_t slot) const {
        QD_CORE_ASSERT(rendererId_);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererId_);
    }
}
