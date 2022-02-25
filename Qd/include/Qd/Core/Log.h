#pragma once

#include <spdlog/spdlog.h> // IWYU pragma: keep

namespace Qd {
    void initLogging();
}

// Core log macros
#define QD_CORE_TRACE(...) spdlog::get("core")->trace(__VA_ARGS__)
#define QD_CORE_INFO(...) spdlog::get("core")->info(__VA_ARGS__)
#define QD_CORE_WARN(...) spdlog::get("core")->warn(__VA_ARGS__)
#define QD_CORE_ERROR(...) spdlog::get("core")->error(__VA_ARGS__)
#define QD_CORE_CRITICAL(...) spdlog::get("core")->critical(__VA_ARGS__)

// Client log macros
#define QD_TRACE(...) spdlog::get("app")->trace(__VA_ARGS__)
#define QD_INFO(...) spdlog::get("app")->info(__VA_ARGS__)
#define QD_WARN(...) spdlog::get("app")->warn(__VA_ARGS__)
#define QD_ERROR(...) spdlog::get("app")->error(__VA_ARGS__)
#define QD_CRITICAL(...) spdlog::get("app")->critical(__VA_ARGS__)
