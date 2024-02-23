#include "core/config.hpp"
#include "core/game.hpp"

#include "particle_example.hpp"
#include "player.hpp"

int main(int argv, char **args)
{
  adv::Config conf;
  conf.title = "Some Squares";
  adv::Game game(conf);

  std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(
      200 * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL, adv::Point(0, 0),
      {0xFF, 0x00, 0x00}, 38 * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL));
  game.scene()->add_child(player);
  game.scene()->register_collideable(player, true);

  std::shared_ptr<ParticleExample> psystem =
      std::make_shared<ParticleExample>(2000);
  game.scene()->add_child(psystem);

  // srand(time(NULL));
  // for (int i = 0; i < 50; i++)
  // {
  //   int size = 60 * adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL;
  //   std::shared_ptr<Box> box = std::shared_ptr<Box>(new Box(
  //       0,
  //       adv::Point(rand() % (conf.screen_width *
  //                                adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL -
  //                            size) +
  //                      size,
  //                  rand() % (conf.screen_height *
  //                                adv::globals::WORLD_DIST_PER_DISPLAY_PIXEL -
  //                            size) +
  //                      size),
  //       {0x00, 0x00, 0xFF}, rand() % size + (size / 4)));
  //   game.scene()->add_child(box);
  //   game.scene()->register_collideable(box, false);
  // }

  game.run();

  return 0;
}
