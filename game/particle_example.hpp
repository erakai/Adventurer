#pragma once

#include "core/input.hpp"
#include "particles/particle.hpp"
#include "particles/particle_system.hpp"
#include "player.hpp"

class ParticleExample : public adv::ParticleSystem
{
public:
  ParticleExample(size_t max_particles, std::shared_ptr<Player> player);
  void update(long delta) override;

private:
  void on_click(adv::input::MouseEventType m, int mouse_x, int mouse_y);

  std::shared_ptr<Player> player;

  adv::ParticleProps fire_props;
  adv::ParticleProps snow_props;
  adv::ParticleProps magic_props;
  adv::ParticleProps lightning_props;
  long ms_since_last_particle = 0;
};
