#include "particle_example.hpp"
#include "core/input.hpp"
#include "particles/particle.hpp"
#include "particles/particle_system.hpp"
#include "utils/color.hpp"
#include "utils/globals.hpp"
#include "utils/vector2f.hpp"

ParticleExample::ParticleExample(size_t max_particles)
    : adv::ParticleSystem(max_particles)
{
  auto func = [this](adv::input::MouseEventType m, int mouse_x, int mouse_y)
  { on_click(m, mouse_x, mouse_y); };
  adv::input::mouse_hook(func);

  fire_props.mode = adv::PARTICLE_GRAVITY;
  fire_props.velocity = adv::Vector2f(0, -200);
  fire_props.velocity_variation = adv::Vector2f(1, 20);
  fire_props.pos_variation = adv::Point(500, 500);
  fire_props.start_color = {201, 15, 12};
  fire_props.end_color = {250, 108, 47};
  fire_props.start_size = 20;
  fire_props.end_size = 5;
  fire_props.lifetime = 4000;

  snow_props.mode = adv::PARTICLE_GRAVITY;
  snow_props.velocity = adv::Vector2f(0, 800);
  snow_props.velocity_variation = adv::Vector2f(0, 20);
  snow_props.start_pos = adv::Point(7400, -50);
  snow_props.pos_variation = adv::Point(7400, 500);
  snow_props.start_color = {163, 171, 207};
  snow_props.end_color = {19, 33, 97};
  snow_props.start_size = 10;
  snow_props.end_size = 8;
  snow_props.lifetime = 10000;

  magic_props.mode = adv::PARTICLE_ROTATION;
  magic_props.pos_variation = adv::Point(350, 350);
  magic_props.start_radius = 0;
  magic_props.radius_delta = 800;
  magic_props.radius_delta_variation = 200;
  magic_props.start_theta = M_PI / 4;
  magic_props.theta_delta = M_PI;
  magic_props.theta_delta_variation = M_PI / 4;
  magic_props.start_color = {80, 25, 117};
  magic_props.end_color = {255, 255, 255};
  magic_props.start_size = 15;
  magic_props.end_size = 5;
  magic_props.lifetime = 4000;
}

void ParticleExample::update(long delta)
{
  ParticleSystem::update(delta);
  ms_since_last_particle += delta;
  if (ms_since_last_particle > 200)
  {
    ms_since_last_particle = 0;
    emit(snow_props);
  }
}

void ParticleExample::on_click(adv::input::MouseEventType m, int mouse_x,
                               int mouse_y)
{
  adv::Point start_pos =
      adv::Point(mouse_x * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL,
                 mouse_y * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL);

  if (m == adv::input::LEFT_MOUSE_BUTTON_PRESS ||
      m == adv::input::LEFT_MOUSE_BUTTON_DRAG)
  {
    fire_props.start_pos = start_pos;
    for (int i = 0; i < 3; i++)
      emit(fire_props);
  }
  else if (m == adv::input::RIGHT_MOUSE_BUTTON_PRESS ||
           m == adv::input::RIGHT_MOUSE_BUTTON_DRAG)
  {
    magic_props.start_pos = start_pos;
    for (int i = 0; i < 6; i++)
    {
      // magic_props.start_theta *= -1;
      // magic_props.theta_delta *= -1;

      emit(magic_props);
    }
  }
}
