#pragma once

#include "SDL_render.h"
#include "core/scene_resource.hpp"
#include "node.hpp"
#include "objs/game_object.hpp"
#include "utils/quadtree.hpp"
#include "utils/rect.hpp"

#include <string>
#include <vector>

namespace adv
{

class Scene : public Node
{
public:
  Scene(std::string name, Rect scene_size);
  Scene(std::string name, Rect scene_size, std::shared_ptr<SceneResource> res);

  void load_resources(SDL_Renderer *renderer);

  std::shared_ptr<QuadTree> get_stationary_collision_tree();
  std::shared_ptr<QuadTree> get_moving_collision_tree();

  void register_collideable(std::shared_ptr<GameObject> obj, bool will_move);

  void update(long delta) override;
  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;

  std::string name() { return title; }
  std::shared_ptr<SceneResource> res() { return resources; }

private:
  std::string title;
  Rect scene_size;

  std::shared_ptr<SceneResource> resources;

  std::vector<std::shared_ptr<GameObject>> moving_scene_objects;
  std::vector<std::shared_ptr<GameObject>> stationary_scene_objects;

  std::shared_ptr<QuadTree> stationary_collision_tree;
  std::shared_ptr<QuadTree> moving_collision_tree;
  bool must_update_stationary_tree = false;
  void recreate_tree(std::shared_ptr<QuadTree> tree,
                     std::vector<std::shared_ptr<GameObject>> &objs);
};

}; // namespace adv
