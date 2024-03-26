#pragma once

#include "core/scene_resource.hpp"
#include "display/texture.hpp"

using namespace adv;

class EditorResource : public SceneResource
{
public:
  void load_textures(SDL_Renderer *renderer) override
  {
    textures["box"] = Texture(renderer, "assets/worldedit/box.png");
    textures["mouse"] = Texture(renderer, "assets/worldedit/mouse.png");

    // Temporary
    textures["tiles"] =
        Texture(renderer, "assets/game/RF_Catacombs_v1.0/mainlevbuild.png");
    textures["tiles"].register_sprite("floor", {832, 224, 16, 16});
  }
};
