#pragma once

#include "SDL_render.h"
#include "display/texture.hpp"
#include <string>
#include <unordered_map>

namespace adv
{

class SceneResource
{
public:
  virtual ~SceneResource()
  {
    for (auto &pair : textures)
    {
      pair.second.close();
    }
  }

  virtual void load_textures(SDL_Renderer *renderer) {}

  std::unordered_map<std::string, Texture> textures;
};

} // namespace adv
