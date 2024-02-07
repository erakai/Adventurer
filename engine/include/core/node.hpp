#pragma once

#include <algorithm>
#include <vector>

namespace adv
{

class Node
{
  public:
    virtual ~Node() {}
    virtual void update(long delta) = 0;
    virtual void render(long delta) = 0;

    void update_children(long delta);
    void render_children(long delta);
    void add_child(std::shared_ptr<Node> n);
    void remove_child(std::shared_ptr<Node> n);
  
  private:
    std::vector<std::shared_ptr<Node>> children;

};

};