#include "core/scene.hpp"

using namespace adv;

void Scene::add_child(Node *u)
{
  children.push_back(u);
}

void Scene::update(long delta)
{
  update_children(delta);
}

void Scene::render(long delta)
{
  for (auto &u: children)
  {
    u->render(delta);
  }
}