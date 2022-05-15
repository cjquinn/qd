#include <memory>

#include <Qd/Application.h>
#include <Qd/EntryPoint.h>

class Sandbox : public Qd::Application {
public:
    Sandbox() : Application("Sandbox") {}

    ~Sandbox() override = default;
};

std::unique_ptr<Qd::Application> Qd::createApplication() {
    return std::make_unique<Sandbox>();
}
