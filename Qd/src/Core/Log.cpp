#include "Qd/Core/Log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Qd {
    void initLogging() {
        spdlog::stdout_color_mt("app");
        spdlog::stdout_color_mt("core");

        spdlog::set_pattern("%^[%T] %n: %v%$");
    }
}
