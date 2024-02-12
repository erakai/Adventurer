#include "core/scene.hpp"

using namespace adv;

void Scene::update(long delta)
{
  update_children(delta);

  collision_tree->clear();

  auto it = scene_objects.begin();
  while (it != scene_objects.end())
  {
    auto obj = it->get();
    if (obj->is_marked_for_death())
    {
      it = scene_objects.erase(it);
    }
    else
    {
      collision_tree->insert(*it);
      it++;
    }

  }
  for (auto &obj: scene_objects)
  {
    collision_tree->insert(obj);
  }
}

void Scene::render(SDL_Renderer* renderer, long delta, Rect viewport)
{
  render_children(renderer, delta, viewport);

  if (globals::COLLISION_DEBUG) collision_tree->debug_render(renderer, delta, viewport);
}

void Scene::add_child_object(std::shared_ptr<GameObject> obj)
{
  obj->set_quadtree(collision_tree);

  add_child(obj);
  scene_objects.push_back(obj);
}