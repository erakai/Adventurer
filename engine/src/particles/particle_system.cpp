#include "particles/particle_system.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "particles/particle.hpp"
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

    if (!particle.ignore_camera_movement)
    {
      particle.update_display_position(viewport);
      if (!(particle.display_pos().x() + particle.size().w > 0 &&
            particle.display_pos().x() < viewport.width() &&
            particle.display_pos().y() + particle.size().h > 0 &&
            particle.display_pos().y() < viewport.height()))
      {
        continue;
      }
    }
    else
    {
      particle.update_display_position(
          Rect(0, 0, viewport.width(), viewport.height()));
    }

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

    if (particle.mode == PARTICLE_GRAVITY)
    {
      particle.velocity = particle.velocity + (particle.accel / 1000.0 * delta);

      Point &position = particle.pos();
      position.x(position.x() + (particle.velocity.x / 1000.0 * delta));
      position.y(position.y() + (particle.velocity.y / 1000.0 * delta));
    }
    else if (particle.mode == PARTICLE_ROTATION)
    {
      particle.radius += (particle.radius_delta / 1000.0 * delta);
      particle.theta += (particle.theta_delta / 1000.0 * delta);
      if (particle.theta > 2 * M_PI)
        particle.theta = particle.theta - (2 * M_PI);

      update_rotating_particle_pos(particle);
    }
    else if (particle.mode == PARTICLE_BOTH)
    {
      particle.velocity = particle.velocity + (particle.accel / 1000.0 * delta);
      particle.origin.x(
          (particle.origin.x() + (particle.velocity.x / 1000.0 * delta)));
      particle.origin.y(
          (particle.origin.y() + (particle.velocity.y / 1000.0 * delta)));
      particle.radius += (particle.radius_delta / 1000.0 * delta);
      particle.theta += (particle.theta_delta / 1000.0 * delta);
      if (particle.theta > 2 * M_PI)
        particle.theta = particle.theta - (2 * M_PI);
      update_rotating_particle_pos(particle);
    }

    particle.time_alive += delta;

    if (particle.time_alive > particle.lifetime)
      particle.active = false;
  }
}

void ParticleSystem::emit(ParticleProps props)
{
  Particle &particle = particle_pool.at(next_free_particle);

  particle.mode = props.mode;
  particle.active = true;
  particle.ignore_camera_movement = props.ignore_camera_movement;

  if (props.mode == PARTICLE_GRAVITY || props.mode == PARTICLE_BOTH)
  {
    particle.pos().x(vary(props.start_pos.x(), props.pos_variation.x()));
    particle.pos().y(vary(props.start_pos.y(), props.pos_variation.y()));

    particle.velocity.x = vary(props.velocity.x, props.velocity_variation.x);
    particle.velocity.y = vary(props.velocity.y, props.velocity_variation.y);
    particle.accel = props.accel;
  }

  if (props.mode == PARTICLE_ROTATION || props.mode == PARTICLE_BOTH)
  {
    particle.origin = props.start_pos;
    particle.radius = vary(props.start_radius, props.start_radius_variation);
    particle.radius_delta =
        vary(props.radius_delta, props.radius_delta_variation);
    particle.theta = vary(props.start_theta, props.start_theta_variation);
    particle.theta_delta = vary(props.theta_delta, props.theta_delta_variation);
    update_rotating_particle_pos(particle);
  }

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
  particle.lifetime = vary(props.lifetime, props.lifetime_variation);

  next_free_particle = (next_free_particle + 1) % particle_pool.size();
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
  if (variance == 0)
    return start;
  return start + (variance * (((rand() % 200) - 100) * 0.01));
}

void ParticleSystem::update_rotating_particle_pos(Particle &particle)
{
  float radius = particle.radius;
  float theta = particle.theta;

  particle.pos().x(particle.origin.x() + radius * cos(theta));
  particle.pos().y(particle.origin.y() + radius * sin(theta));
}
