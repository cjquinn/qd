#pragma once

#include <memory>

#include "qd/application.h"
#include "qd/core/log.h"

namespace qd {
std::unique_ptr<qd::Application> CreateApplication();
};

// NOLINTNEXTLINE
int main() {
  qd::core::InitLogging();
  {
    auto app = qd::CreateApplication();
    app->Run();
  }
}
