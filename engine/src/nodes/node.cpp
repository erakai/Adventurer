#include "nodes/node.hpp"

using namespace adv;

void Node::update_children(long delta)
{
  for (auto &n: children)
  {
    n->update(delta);
    n->update_children(delta);
  }
}

void Node::render_children(long delta, PositionRect viewport)
{
  for (auto &n: children)
  {
    n->render(delta, viewport);
    n->render_children(delta, viewport);
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