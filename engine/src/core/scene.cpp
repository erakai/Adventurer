#include "core/scene.hpp"

using namespace adv;

void Scene::update(long delta)
{
  update_children(delta);

  collision_tree->clear();
  for (auto &obj: scene_objects)
  {
    collision_tree->insert(obj);
  }
}

void Scene::render(SDL_Renderer* renderer, long delta, Rect viewport)
{
  render_children(renderer, delta, viewport);
}

void Scene::add_child_object(std::shared_ptr<GameObject> obj)
{
  obj->set_quadtree(collision_tree);

  add_child(obj);
  scene_objects.push_back(obj);
}