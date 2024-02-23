#include "fire_system.hpp"
#include "particles/particle_system.hpp"
#include "utils/color.hpp"
#include "utils/globals.hpp"
#include "utils/vector2f.hpp"

FireSystem::FireSystem(size_t max_particles)
    : adv::ParticleSystem(max_particles)
{
  auto func = [this](adv::input::MouseEventType m, int mouse_x, int mouse_y)
  { on_click(m, mouse_x, mouse_y); };
  adv::input::mouse_hook(func);

  props.velocity = adv::Vector2f(0, -200);
  props.velocity_variation = adv::Vector2f(1, 20);
  props.pos_variation = adv::Point(500, 500);
  props.start_color = {201, 15, 12};
  props.end_color = {250, 108, 47};
  props.start_size = 20;
  props.end_size = 5;
  props.lifetime = 4000;
}

void FireSystem::on_click(adv::input::MouseEventType m, int mouse_x,
                          int mouse_y)
{
  props.start_pos =
      adv::Point(mouse_x * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL,
                 mouse_y * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL);
  for (int i = 0; i < 3; i++)
    emit(props);
}
