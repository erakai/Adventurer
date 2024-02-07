#pragma once

#include "SDL.h"

#include <string>
#include <iostream>

namespace adv
{

namespace logger
{

void log(std::string s);
void log_sdl(std::string s);

};

};