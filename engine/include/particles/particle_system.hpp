#pragma once

#include "particle.hpp"
#include <vector>

namespace adv
{

class ParticleSystem
{
public:
private:
  bool active = true;

  std::vector<Particle> particles;
  int current_particle_count = 0;

  Point source_position;
  Point position_variance;
};

} // namespace adv
