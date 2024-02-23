#include "snow_system.hpp"
#include "particles/particle_system.hpp"

using namespace adv;

SnowSystem::SnowSystem(size_t max_particles) : ParticleSystem(max_particles)
{
  props.velocity = adv::Vector2f(0, 800);
  props.velocity_variation = adv::Vector2f(0, 20);
  props.start_pos = adv::Point(7400, -50);
  props.pos_variation = adv::Point(7400, 500);
  props.start_color = {163, 171, 207};
  props.end_color = {19, 33, 97};
  props.start_size = 10;
  props.end_size = 8;
  props.lifetime = 10000;
}

void SnowSystem::update(long delta)
{
  ParticleSystem::update(delta);
  ms_since_last_particle += delta;
  if (ms_since_last_particle > 200)
  {
    ms_since_last_particle = 0;
    emit(props);
  }
}
