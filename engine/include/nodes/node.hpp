#pragma once

#include "world/position_rect.hpp"

#include <algorithm>
#include <vector>

namespace adv
{

class Node
{
  public:
    virtual ~Node() {}
    virtual void update(long delta) {}
    virtual void render(long delta, PositionRect viewport) {}

    void update_children(long delta);
    void render_children(long delta, PositionRect viewport);
    void add_child(std::shared_ptr<Node> n);
    void remove_child(std::shared_ptr<Node> n);
  
  private:
    std::vector<std::shared_ptr<Node>> children;

};

};