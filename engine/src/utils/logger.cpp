#include "utils/logger.hpp"

using namespace adv::logger;
using namespace std::chrono;

time_point<system_clock> adv::logger::boot_time = system_clock::now();

void adv::logger::log(std::string message, const std::source_location loc)
{
  std::filesystem::path path(loc.file_name());

  std::cout << "[" << get_current_time()
            << " " << path.filename().string()
            << "(" << loc.line()
            << ":" << loc.column()
            << ")]: " << message
            << std::endl;
}

void adv::logger::log_sdl(std::string message, const std::source_location loc)
{
  log(message + "\n\tSDL_ERROR: " + SDL_GetError());
}

std::string adv::logger::get_current_time()
{
  auto current = system_clock::now();
  auto dur = current - boot_time;

  auto d = duration_cast<duration<long, std::ratio<3600 * 24>>>(dur);
  auto h = duration_cast<hours>(dur -= d);
  auto m = duration_cast<minutes>(dur -= h);
  auto s = duration_cast<seconds>(dur -= m);
  auto ms = duration_cast<milliseconds>(dur -= s);

  return std::format("{:02d}:{:02d}:{:02d}:{:04d}", h.count(), m.count(), s.count(), ms.count());
}