#pragma once

#include <chrono>
#include <source_location>
#include <string>

namespace adv
{

namespace logger
{

extern std::chrono::time_point<std::chrono::system_clock> boot_time;

void log(std::string message,
         const std::source_location location = std::source_location::current());
void log_sdl(std::string message, const std::source_location location =
                                      std::source_location::current());

std::string get_current_time();

}; // namespace logger

}; // namespace adv
