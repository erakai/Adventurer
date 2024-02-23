#pragma once

#include "core/input.hpp"
#include "particles/particle.hpp"
#include "particles/particle_system.hpp"

class FireSystem : public adv::ParticleSystem
{
public:
  FireSystem(size_t max_particles);

private:
  void on_click(adv::input::MouseEventType m, int mouse_x, int mouse_y);

  adv::ParticleProps props;
};
