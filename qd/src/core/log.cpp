#include "qd/core/log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace qd::core {
void InitLogging() {
  spdlog::stdout_color_mt("app");
  spdlog::stdout_color_mt("core");

  spdlog::set_pattern("%^[%T] %n: %v%$");
}
}  // namespace qd::core
