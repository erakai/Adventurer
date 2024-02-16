#pragma once

#include "world/positioned.hpp"

namespace adv
{

class Particle: public Positioned
{
  public:
    bool active = false;

    int start_x = 0;
    int start_y = 0;

    float color_r = 0;
    float color_g = 0;
    float color_b = 0;
    float color_a = 0;

    float delta_color_r = 0;
    float delta_color_g = 0;
    float delta_color_b = 0;
    float delta_color_a = 0;

    float size = 0;
    float delta_size = 0;

    float rotation = 0;
    float delta_rotation = 0;

    float time_to_live = 0;

    struct 
    {
      float delta_x = 0;
      float delta_y = 0;
      float radial_accel = 0;
      float tangential_accel = 0;
    } gravity_mode;

    struct 
    {
      float angle = 0;
      float delta_angle = 0; /* degrees per second */
      float radius = 0;
      float delta_radius = 0;
    } radius_mode;

};

}