#include "core/scene.hpp"

using namespace adv;

void Scene::update(long delta)
{
  update_children(delta);

  recreate_tree(moving_collision_tree, moving_scene_objects);

  if (must_update_stationary_tree) {
    recreate_tree(stationary_collision_tree, stationary_scene_objects);
    must_update_stationary_tree = false;
  } else {
    for (auto &s : stationary_scene_objects) {
      if (s->is_marked_for_death()) {
        recreate_tree(stationary_collision_tree, stationary_scene_objects);
        must_update_stationary_tree = false;
        break;
      }
    }
  }
}

void Scene::recreate_tree(std::shared_ptr<QuadTree> tree,
                          std::vector<std::shared_ptr<GameObject>> &objs)
{
  tree->clear();

  auto it = objs.begin();
  while (it != objs.end()) {
    auto obj = it->get();
    if (obj->is_marked_for_death()) {
      it = objs.erase(it);
    } else {
      tree->insert(*it);
      it++;
    }
  }
}

void Scene::render(SDL_Renderer *renderer, long delta, Rect viewport)
{
  render_children(renderer, delta, viewport);

  if (globals::COLLISION_DEBUG)
    moving_collision_tree->debug_render(renderer, delta, viewport);
  if (globals::COLLISION_DEBUG)
    stationary_collision_tree->debug_render(renderer, delta, viewport);
}

void Scene::register_collideable(std::shared_ptr<GameObject> obj,
                                 bool will_move)
{
  obj->set_quadtrees(moving_collision_tree, stationary_collision_tree);

  if (will_move) {
    moving_scene_objects.push_back(obj);
  } else {
    must_update_stationary_tree = true;
    stationary_scene_objects.push_back(obj);
  }
}
