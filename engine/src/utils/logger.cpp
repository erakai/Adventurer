#include "utils/logger.hpp"

using namespace adv::logger;

void adv::logger::log(std::string s)
{
  std::cout << "LOGGED: " << s << std::endl;
}

void adv::logger::log_sdl(std::string s)
{
  std::cout << "LOGGED: " << s << std::endl;
  std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
}