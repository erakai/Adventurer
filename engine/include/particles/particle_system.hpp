#pragma once

#include "core/node.hpp"
#include "particle.hpp"
#include <vector>

namespace adv
{

class ParticleSystem : public Node
{
public:
  ParticleSystem(){};
  virtual ~ParticleSystem();

  // API for derived class
  virtual void init_with_particles(int particle_num);
  virtual void reset_particle_count(int particle_num);
  virtual bool is_paused() const;
  virtual void pause_emitting();
  virtual void resume_emitting();

  void render(SDL_Renderer *renderer, long delta, Rect viewport) override;
  void update(long delta) override;

  void is_full();
  void reset_system();

protected:
  bool active = true;
  bool kill_self_on_finish = true;

  std::vector<Particle> particle_pool;
  uint32_t next_free_particle;

  Point source_position;
  Point position_variance;
};

} // namespace adv
