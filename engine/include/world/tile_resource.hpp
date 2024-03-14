#pragma once

#include "utils/serializable.hpp"

#include <string>
#include <unordered_map>

namespace adv
{

struct Tile
{
  std::string texture_name = "";
  std::string sprite_name = "none";

  bool impassable = false;
};

class TileResource : public Serializable
{
public:
  std::unordered_map<uint8_t, Tile> tiles;

  void read(std::string filepath) override;
  void write(std::string filepath) override;
};

} // namespace adv
