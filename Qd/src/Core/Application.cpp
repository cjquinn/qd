#include "Qd/Core/Application.h"

#include <iostream>

Qd::Application::Application() = default;

Qd::Application::~Application() = default;

void Qd::Application::run() {
    std::cout << "Hello Steve" << std::endl;
}
