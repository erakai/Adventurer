#pragma once

#include "../components/tiler.hpp"
#include "core/scene.hpp"
#include "world/tile_resource.hpp"

#include <unordered_set>

class Editor : public adv::Scene
{
public:
  Editor();

private:
  std::shared_ptr<Tiler> tiler;

  // https://stackoverflow.com/questions/50888127/how-can-i-use-an-unordered-set-with-a-custom-struct
  std::unordered_set<adv::Tile> tiles_in_use;
};
