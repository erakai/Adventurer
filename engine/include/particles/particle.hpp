#pragma once

#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/vector2f.hpp"
#include "world/positioned.hpp"

namespace adv
{

enum ParticleMode
{
  PARTICLE_GRAVITY,
  PARTICLE_ROTATION
};

struct ParticleProps
{
  ParticleMode mode = PARTICLE_GRAVITY;

  Point start_pos;
  Point pos_variation;

  // Gravity Props
  Vector2f velocity;
  Vector2f velocity_variation;
  Vector2f accel;

  // Rotation Props
  float start_radius;
  float radius_delta;
  float radius_delta_variation;
  float start_theta;
  float theta_delta;
  float theta_delta_variation;

  Color start_color;
  Color end_color;

  float start_size;
  float end_size;
  float size_variation;

  long lifetime = 1000; // ms
};

class Particle : public Positioned
{
public:
  bool active = false;
  ParticleMode mode = PARTICLE_GRAVITY;

  // Gravity
  Vector2f velocity;
  Vector2f accel;

  // Rotation
  Point origin;
  float radius = 0;
  float radius_delta = 0;
  float theta = 0;
  float theta_delta = 0;

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

  long time_alive = 0;
  long lifetime = 0;
};

} // namespace adv
