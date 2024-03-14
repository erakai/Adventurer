#pragma once

#include "chunk.hpp"
#include "core/node.hpp"
#include "utils/globals.hpp"
#include "utils/serializable.hpp"

namespace adv
{

class World : public Node, public Serializable
{
public:
  World(std::string filepath);

  void attach(std::shared_ptr<GameObject> adv);

  void register_object(std::shared_ptr<GameObject> obj);
  Chunk &find_chunk(Point p);

  void update(long delta) override;
  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;

  void read(std::string filepath) override;
  void write(std::string filepath) override;

private:
  Chunk chunks[globals::CHUNK_RENDER_DISTANCE][globals::CHUNK_RENDER_DISTANCE];
  std::shared_ptr<GameObject> attached_to = nullptr;

  std::shared_ptr<TileResource> resource;

  int loaded_radius;
  int visible_radius;

  void move_objects_between_chunks();
};

} // namespace adv
