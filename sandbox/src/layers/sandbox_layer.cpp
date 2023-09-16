#include "sandbox_layer.h"

#include <qd/core/base.h>
#include <qd/events/event.h>
#include <qd/events/window_event.h>
#include <qd/renderer/render_command.h>

namespace sandbox {
void SandboxLayer::OnAttach() {
  shader_.Init(
      R"(
        #version 330 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        uniform mat4 u_ViewProjection;

        out vec2 v_TexCoord;

        void main()
        {
            gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
            v_TexCoord = a_TexCoord;
        }
      )",
      R"(
        #version 330 core

        in vec2 v_TexCoord;

        out vec4 color;

        uniform sampler2D u_Texture;

        void main()
        {
            color = texture(u_Texture, v_TexCoord);
        }
      )");

  texture_.Init("assets/textures/aliens.png");
  texture_.Bind();

  shader_.Bind();
  shader_.SetUniform1i("u_Texture", 0);

  vertex_array_.Init();

  float vertices[] = {
      -0.5F, -0.5F, 0.0F, 0.0F,  // bottom left
      -0.5F, 0.5F,  0.0F, 1.0F,  // top left
      0.5F,  -0.5F, 1.0F, 0.0F,  // bottom right
      0.5F,  0.5F,  1.0F, 1.0F,  // top right
  };

  vertex_array_.SetVertexBuffer(
      vertices, sizeof(vertices),
      {
          {qd::renderer::ShaderType::kFloat, 2},  // position
          {qd::renderer::ShaderType::kFloat, 2},  // texture
      });

  uint32_t indices[] = {
      0, 1, 2, 2, 1, 3,
  };
  vertex_array_.SetIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));
}

void SandboxLayer::OnDetach() {}

void SandboxLayer::OnEvent(qd::events::Event &event) {
  qd::events::Dispatcher dispatcher{event};

  dispatcher.Dispatch<qd::events::WindowResizedEvent>(
      QD_BIND(HandleWindowResized));
}

void SandboxLayer::Update() {
  qd::renderer::render_command::SetClearColor({0.1F, 0.1F, 0.1F, 1.0});
  qd::renderer::render_command::Clear();

  shader_.Bind();
  shader_.SetUniformMat4("u_ViewProjection", camera_.GetViewProjection());
  vertex_array_.Bind();
  qd::renderer::render_command::Draw(vertex_array_);
}

void SandboxLayer::HandleWindowResized(qd::events::WindowResizedEvent &event) {
  camera_.SetProjection(static_cast<float>(event.GetWidth()) /
                        static_cast<float>(event.GetHeight()));
}
}  // namespace sandbox
