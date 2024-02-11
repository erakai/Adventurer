#pragma once

#include "node.hpp"
#include "utils/logger.hpp"

#include <string>
#include <vector>

namespace adv
{

class Scene: public Node
{
  public:
    Scene(std::string name) :
      title(name) {
        logger::log("Scene (\"" + name + "\") created");
      }
    
    void update(long delta) override;
    void render(SDL_Renderer* renderer, long delta, Rect viewport) override;

    std::string name() { return title; }

  private:
    std::string title;

};

};