#pragma once

#include "core/scene_resource.hpp"
#include "display/texture.hpp"

class TestResource : public adv::SceneResource
{
public:
  void load_textures(SDL_Renderer *renderer) override
  {
    textures["player"] = adv::Texture(renderer, "assets/fire.png");
    textures["box"] = adv::Texture(renderer, "assets/box.png");
  }
};
