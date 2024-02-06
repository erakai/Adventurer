#include "core/scene.hpp"

using namespace adv;

void Scene::add_child(Updatable *u)
{
  children.push_back(u);
}

void Scene::update(long delta)
{
  for (auto &u: children)
  {
    u->update(delta);
  }
}

void Scene::render(long delta)
{
  for (auto &u: children)
  {
    u->render(delta);
  }
}