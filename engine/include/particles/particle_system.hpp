#pragma once

#include "core/node.hpp"
#include "particle.hpp"
#include <vector>

namespace adv
{

class ParticleSystem : public Node
{
public:
  ParticleSystem(size_t max_particles);
  virtual ~ParticleSystem(){};

  virtual void update(long delta) override;
  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;
  void emit(ParticleProps props);

  void reset_system();
  bool is_full() const;
  void toggle_pause();
  bool is_paused() const;

protected:
  bool active = true;

  std::vector<Particle> particle_pool;
  uint32_t next_free_particle;

private:
  float vary(float start, float variance);
};

} // namespace adv
