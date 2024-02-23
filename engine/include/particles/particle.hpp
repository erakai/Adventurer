#pragma once

#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/vector2f.hpp"
#include "world/positioned.hpp"

namespace adv
{

struct ParticleProps
{
  Point start_pos;
  Point pos_variation;

  Vector2f velocity;
  Vector2f velocity_variation;

  Vector2f accel;

  Color start_color;
  Color end_color;

  float start_size;
  float end_size;
  float size_variation;

  float rotation;
  float delta_rotation;

  long lifetime = 1000; // ms
};

class Particle : public Positioned
{
public:
  bool active = false;

  Vector2f velocity;
  Vector2f accel;

  float s_color_r = 0;
  float s_color_g = 0;
  float s_color_b = 0;
  float s_color_a = 0;

  float e_color_r = 0;
  float e_color_g = 0;
  float e_color_b = 0;
  float e_color_a = 0;

  float s_size = 0;
  float e_size = 0;

  // TODO: Make rotation used
  float rotation = 0;
  float delta_rotation = 0;

  long time_alive = 0;
  long lifetime = 0;
};

} // namespace adv
