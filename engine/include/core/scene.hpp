#pragma once

#include "nodes/node.hpp"
#include "world/position_rect.hpp"

#include <string>
#include <vector>

namespace adv
{

class Scene: public Node
{
  public:
    Scene(std::string name) :
      title(name) {}
    
    void add_child(Node* u);

    void update(long delta) override;
    void render(long delta, PositionRect viewport) override;

    std::string name() { return title; }

  private:
    std::string title;
    std::vector<Node*> children;

};

};