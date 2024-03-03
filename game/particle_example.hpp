#pragma once

#include "core/input.hpp"
#include "particles/particle.hpp"
#include "particles/particle_system.hpp"

class ParticleExample : public adv::ParticleSystem
{
public:
  ParticleExample(size_t max_particles);
  void update(long delta) override;

private:
  void on_click(adv::input::MouseEventType m, int mouse_x, int mouse_y);

  adv::ParticleProps fire_props;
  adv::ParticleProps snow_props;
  adv::ParticleProps magic_props;
  adv::ParticleProps lightning_props;
  long ms_since_last_particle = 0;
};
