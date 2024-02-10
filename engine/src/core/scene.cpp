#include "core/scene.hpp"

using namespace adv;

void Scene::update(long delta)
{
  update_children(delta);
}

void Scene::render(SDL_Renderer* renderer, long delta, Rect viewport)
{
  render_children(renderer, delta, viewport);
}