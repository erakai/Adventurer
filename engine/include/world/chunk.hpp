#pragma once

#include "core/node.hpp"
#include "objs/game_object.hpp"
#include "tile_resource.hpp"
#include "utils/globals.hpp"
#include "utils/quadtree.hpp"
#include "utils/serializable.hpp"

#include <string>
#include <vector>

namespace adv
{

struct ChunkIndex
{
  std::string filepath = "";
  uint16_t location_in_file = 0;
};

class Chunk : public Node, public Serializable
{
public:
  Chunk(Rect bounds, ChunkIndex index);

  void register_object(std::shared_ptr<GameObject> obj);
  std::vector<std::shared_ptr<GameObject>> possible_collisions(GameObject obj);

  void update(long delta) override;
  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;

  void read(std::string filepath) override;
  void write(std::string filepath) override;

private:
  uint8_t tile_map[globals::TILES_PER_CHUNK][globals::TILES_PER_CHUNK] = {{0}};

  std::vector<std::shared_ptr<GameObject>> moveable_objs;
  std::vector<std::shared_ptr<GameObject>> stationary_objs;
  void clean_invalid_objects();

  std::shared_ptr<QuadTree> moveable_tree;
  std::shared_ptr<QuadTree> stationary_tree;
  void recreate_tree(std::shared_ptr<QuadTree> tree,
                     std::vector<std::weak_ptr<Positioned>> &objs);

  std::weak_ptr<TileResource> resource;

  Rect chunk_bounds;
  ChunkIndex index;
  bool valid = false;
};

} // namespace adv
