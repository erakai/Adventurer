#pragma once

#include "node.hpp"

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
    void render(SDL_Renderer* renderer, long delta, Rect viewport) override;

    std::string name() { return title; }

  private:
    std::string title;

};

};