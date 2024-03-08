#include "core/config.hpp"
#include "core/game.hpp"
#include "core/scene.hpp"
#include "display/camera.hpp"

#include "box.hpp"
#include "particle_example.hpp"
#include "player.hpp"
#include "test_resource.hpp"

#include "SDL.h"
#include "utils/globals.hpp"

int main(int argv, char **args)
{
  adv::Config conf;

  // Create Scene =============================================================
  std::shared_ptr<adv::Scene> scene = std::make_shared<adv::Scene>(
      "Test",
      adv::Rect(0, 0, 1280 * 4 * adv::globals::SUBPIXELS,
                720 * 4 * adv::globals::SUBPIXELS),
      std::make_shared<TestResource>());

  // Create Game ==============================================================
  adv::Game game(conf, scene);

  // Create Player ============================================================
  std::shared_ptr<Player> player = std::shared_ptr<Player>(
      new Player(400 * adv::globals::SUBPIXELS, adv::Point(20000, 20000)));

  // Create Camera ============================================================
  std::shared_ptr<adv::Camera> cam = std::make_shared<adv::Camera>(
      adv::CameraType::CENTERED_FOLLOW, conf.screen_width, conf.screen_height);
  cam->attach(player);
  game.set_camera(cam);

  // Create Boxes =============================================================
  srand(time(NULL));
  for (int i = 0; i < 100; i++)
  {
    int size = 150 * adv::globals::SUBPIXELS;
    std::shared_ptr<Box> box = std::shared_ptr<Box>(new Box(
        0,
        adv::Point(
            rand() % (4 * conf.screen_width * adv::globals::SUBPIXELS - size) +
                size,
            rand() % (4 * conf.screen_height * adv::globals::SUBPIXELS - size) +
                size),
        {0x00, 0x00, 0xFF}, rand() % size + (size / 4)));
    game.scene()->add_child(box);
    game.scene()->register_collideable(box, false);
  }

  // Create Particle System ===================================================
  std::shared_ptr<ParticleExample> psystem =
      std::make_shared<ParticleExample>(20000, player);
  game.scene()->add_child(psystem);

  // Add player last so they render on top
  game.scene()->add_child(player);
  game.scene()->register_collideable(player, true);
  game.run();

  return 0;
}
