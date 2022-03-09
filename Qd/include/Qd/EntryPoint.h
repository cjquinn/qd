#pragma once

#include "Qd/Core/Application.h"
#include "Qd/Core/Log.h"

namespace Qd {
    Application* createApplication();
};

int main() {
    Qd::initLogging();
    auto app = Qd::createApplication();
    app->run();
    delete app;
}
