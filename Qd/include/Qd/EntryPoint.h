#pragma once

#include <memory>

#include "Qd/Application.h"
#include "Qd/Core/Log.h"

namespace Qd {
std::unique_ptr<Qd::Application> createApplication();
};

int main() {
  Qd::Core::initLogging();
  {
    auto app = Qd::createApplication();
    app->run();
  }
}
