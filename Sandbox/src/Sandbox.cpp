#include <Qd/Core/Application.h>
#include <Qd/EntryPoint.h>

class Sandbox : public Qd::Application {
 public:
    Sandbox() = default;

    ~Sandbox() override = default;
};

Qd::Application* Qd::createApplication() {
    return new Sandbox();
}
