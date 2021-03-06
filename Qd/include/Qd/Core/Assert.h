#pragma once

#include <filesystem>
#include <csignal>

#include "Qd/Core/Log.h"

#define QD_CORE_ASSERT(check, ...) { if (!check) { QD_CORE_ERROR("Assertion '{0}' failed at {1}:{2}", #check, std::filesystem::path(__FILE__).filename().string(), __LINE__); raise(SIGTRAP); }}
