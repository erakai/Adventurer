#pragma once

#include "utils/serializable.hpp"

#include <functional>
#include <string>
#include <unordered_map>

namespace adv
{

struct Tile
{
  std::string texture_name = "";
  std::string sprite_name = "none";

  bool impassable = false;
  bool valid = false;

  bool operator==(const Tile &other) const = default;
};

class TileResource : public Serializable
{
public:
  std::unordered_map<uint8_t, Tile> tiles;

  void read(std::string filepath) override;
  void write(std::string filepath) override;
};

} // namespace adv

// https://stackoverflow.com/questions/25594644/warning-specialization-of-template-in-different-namespace
namespace std
{
template <> struct std::hash<adv::Tile>
{
  std::size_t operator()(const adv::Tile &k) const
  {
    std::size_t res = 17;
    res = res * 31 + hash<string>()(k.texture_name);
    res = res * 31 + hash<string>()(k.sprite_name);
    res = res * 31 + hash<bool>()(k.impassable);
    res = res * 31 + hash<bool>()(k.valid);
    return res;
  }
};
} // namespace std
