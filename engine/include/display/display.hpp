#pragma once

#include "core/updatable.hpp"
#include "core/scene.hpp"

namespace adv
{

class Display
{
  public:
    Display();

    void render_scene(Scene& scene, long delta);
  private:
    

};

};