#pragma once

#include "core/node.hpp"
#include "core/scene.hpp"

namespace adv
{

class Display
{
  public:
    Display();

    void render_scene(std::shared_ptr<Scene> scene, long delta);
  private:
    

};

};