#pragma once

#include "node.hpp"
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
    
    void update(long delta) override;
    void render(SDL_Renderer* renderer, long delta, PositionRect viewport) override;

    std::string name() { return title; }

  private:
    std::string title;

};

};