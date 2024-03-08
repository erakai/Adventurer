#pragma once

#include "core/scene_resource.hpp"
#include "display/texture.hpp"

using namespace adv;

class TestResource : public SceneResource
{
public:
  void load_textures(SDL_Renderer *renderer) override
  {
    textures["player"] = Texture(renderer, "assets/player.png");
    textures["player"].register_sprite("still", {18, 22, 13, 21});

    textures["decor"] =
        Texture(renderer, "assets/RF_Catacombs_v1.0/decorative.png");
    textures["decor"].register_sprite("tomb", {5, 101, 37, 27});
  }
};
