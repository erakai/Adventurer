#pragma once

#include "node.hpp"
#include "objs/game_object.hpp"
#include "utils/logger.hpp"
#include "utils/rect.hpp"
#include "utils/quadtree.hpp"

#include <string>
#include <vector>

namespace adv
{

class Scene: public Node
{
  public:
    Scene(std::string name, Rect bounds) :
      title(name), bounds(bounds) {
        moving_collision_tree = std::make_shared<QuadTree>(bounds);
        stationary_collision_tree = std::make_shared<QuadTree>(bounds);
        logger::log("Scene (\"" + name + "\") created");
      }
    
    std::vector<std::shared_ptr<Positioned>> get_possible_collisions(GameObject obj);
    void register_collideable(std::shared_ptr<GameObject> obj, bool will_move);

    void update(long delta) override;
    void render(SDL_Renderer* renderer, long delta, Rect viewport) override;

    std::string name() { return title; }

  private:
    void recreate_tree(std::shared_ptr<QuadTree> tree,
      std::vector<std::shared_ptr<GameObject>> &objs);

    std::string title;

    Rect bounds;

    std::shared_ptr<QuadTree> stationary_collision_tree;
    std::shared_ptr<QuadTree> moving_collision_tree;

    std::vector<std::shared_ptr<GameObject>> moving_scene_objects;
    std::vector<std::shared_ptr<GameObject>> stationary_scene_objects;
    bool must_update_stationary_tree = false;

};

};