#include "core/config.hpp"
#include "core/game.hpp"
#include "core/scene.hpp"

int main(int argv, char **args)
{
  adv::Config conf;
  conf.screen_width = 1640;
  conf.screen_height = 924;

  std::shared_ptr<adv::Scene> scene = std::make_shared<adv::Scene>(
      "World Edit", adv::Rect({conf.screen_width * adv::globals::SUBPIXELS,
                               conf.screen_height * adv::globals::SUBPIXELS}));
  adv::Game game(conf, scene);

  game.run();

  return 0;
}
