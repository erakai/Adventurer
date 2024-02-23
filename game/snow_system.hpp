#pragma once

#include "particles/particle.hpp"
#include "particles/particle_system.hpp"

class SnowSystem : public adv::ParticleSystem
{
public:
  SnowSystem(size_t max_particles);

  void update(long delta) override;

private:
  adv::ParticleProps props;
  long ms_since_last_particle = 0;
};
