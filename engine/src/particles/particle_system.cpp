#include "particles/particle_system.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <cmath>

using namespace adv;

ParticleSystem::ParticleSystem(size_t max_particles)
{
  next_free_particle = 0;
  particle_pool.resize(max_particles);

  srand(time(NULL));
}

void ParticleSystem::render(SDL_Renderer *renderer, long delta, Rect viewport)
{
  if (!active)
    return;

  for (auto &particle : particle_pool)
  {
    if (!particle.active)
      continue;

    particle.update_display_position(viewport);

    float life_ratio =
        (particle.time_alive / static_cast<double>(particle.lifetime));

    int c_size = static_cast<int>(
        std::lerp(particle.s_size, particle.e_size, life_ratio));

    int r = static_cast<int>(
        std::lerp(particle.s_color_r, particle.e_color_r, life_ratio));
    int g = static_cast<int>(
        std::lerp(particle.s_color_g, particle.e_color_r, life_ratio));
    int b = static_cast<int>(
        std::lerp(particle.s_color_b, particle.e_color_g, life_ratio));
    int a = static_cast<int>(
        std::lerp(particle.s_color_a, particle.e_color_a, life_ratio));

    SDL_Rect p_rect = {particle.display_pos().x(), particle.display_pos().y(),
                       c_size, c_size};
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &p_rect);
  }
}

void ParticleSystem::update(long delta)
{
  if (!active)
    return;

  for (auto &particle : particle_pool)
  {
    if (!particle.active)
      continue;

    particle.rotation += (particle.delta_rotation * delta);
    particle.velocity = particle.velocity + (particle.accel / 1000.0 * delta);

    Point &position = particle.pos();
    position.x(position.x() + (particle.velocity.x / 1000.0 * delta));
    position.y(position.y() + (particle.velocity.y / 1000.0 * delta));

    particle.time_alive += delta;

    if (particle.time_alive > particle.lifetime)
      particle.active = false;
  }
}

void ParticleSystem::emit(ParticleProps props)
{
  Particle &particle = particle_pool.at(next_free_particle);

  particle.active = true;
  particle.pos().x(vary(props.start_pos.x(), props.pos_variation.x()));
  particle.pos().y(vary(props.start_pos.y(), props.pos_variation.y()));

  particle.velocity.x = vary(props.velocity.x, props.velocity_variation.x);
  particle.velocity.y = vary(props.velocity.y, props.velocity_variation.y);
  particle.accel = props.accel;

  particle.s_color_r = props.start_color.r;
  particle.s_color_g = props.start_color.g;
  particle.s_color_b = props.start_color.b;
  particle.s_color_a = props.start_color.opacity;
  particle.e_color_r = props.end_color.r;
  particle.e_color_g = props.end_color.g;
  particle.e_color_b = props.end_color.b;
  particle.e_color_a = props.end_color.opacity;

  particle.s_size = vary(props.start_size, props.size_variation);
  particle.e_size = props.end_size;

  particle.time_alive = 0;
  particle.lifetime = props.lifetime;

  particle.rotation = props.rotation;
  particle.delta_rotation = props.delta_rotation;

  next_free_particle = (++next_free_particle) % particle_pool.size();
}

void ParticleSystem::reset_system()
{
  for (auto &particle : particle_pool)
  {
    particle.active = false;
  }

  next_free_particle = 0;
}

bool ParticleSystem::is_full() const
{
  return particle_pool.at(next_free_particle).active;
}

void ParticleSystem::toggle_pause()
{
  active = !active;
}

bool ParticleSystem::is_paused() const
{
  return active;
}

float ParticleSystem::vary(float start, float variance)
{
  return start + (variance * (((rand() % 200) - 100) * 0.01));
}
