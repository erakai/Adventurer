#include "particles/particle_system.hpp"
#include "SDL_render.h"

using namespace adv;

ParticleSystem::ParticleSystem(size_t max_particles)
{
  next_free_particle = 0;
  particle_pool.resize(max_particles);
}

void ParticleSystem::render(SDL_Renderer *renderer, long delta, Rect viewport)
{
}

void ParticleSystem::update(long delta)
{
}

void ParticleSystem::emit(ParticleProps props)
{
}

void ParticleSystem::reset_system()
{
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
