#include "core/config.hpp"
#include "core/game.hpp"

#include "box.hpp"
#include "player.hpp"

#include <time.h>

int main(int argv, char **args)
{
  adv::Config conf;
  conf.title = "Some Squares";
  adv::Game game(conf);

  std::shared_ptr<Player> player = std::shared_ptr<Player>(
      new Player(5000, adv::Point(0, 0), {0xFF, 0x00, 0x00}, 500));
  game.scene()->add_child(player);
  game.scene()->register_collideable(player, true);

  srand(time(NULL));
  for (int i = 0; i < 15; i++) {
    int size = 700;
    std::shared_ptr<Box> box = std::shared_ptr<Box>(
        new Box(0,
                adv::Point(rand() % (conf.screen_width * 10 - size) + size,
                           rand() % (conf.screen_height * 10 - size) + size),
                {0x00, 0x00, 0xFF}, rand() % 700 + 200));
    game.scene()->add_child(box);
    game.scene()->register_collideable(box, false);
  }

  game.run();

  return 0;
}
