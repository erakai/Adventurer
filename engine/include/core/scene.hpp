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
        collision_tree = std::make_shared<QuadTree>(bounds);
        logger::log("Scene (\"" + name + "\") created");
      }
    
    void add_child_object(std::shared_ptr<GameObject> obj);
    void update(long delta) override;
    void render(SDL_Renderer* renderer, long delta, Rect viewport) override;

    std::string name() { return title; }

  private:
    std::string title;

    Rect bounds;
    std::shared_ptr<QuadTree> collision_tree;
    std::vector<std::shared_ptr<GameObject>> scene_objects;

};

};