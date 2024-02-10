#include "core/node.hpp"

using namespace adv;

void Node::update_children(long delta)
{
  for (auto &n: children)
  {
    n->update(delta);
    n->update_children(delta);
  }
}

void Node::render_children(SDL_Renderer* renderer, long delta, Rect viewport)
{
  for (auto &n: children)
  {
    n->render(renderer, delta, viewport);
    n->render_children(renderer, delta, viewport);
  }
}

void Node::add_child(std::shared_ptr<Node> n)
{
  children.push_back(n);
}

void Node::remove_child(std::shared_ptr<Node> n)
{
  children.erase(
    std::remove(children.begin(), children.end(), n), children.end()
  );
}