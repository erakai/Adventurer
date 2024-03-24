#include "core/config.hpp"
#include "core/scene.hpp"
#include "views/editor.hpp"
#include "worldedit.hpp"

int main(int argv, char **args)
{
  adv::Config conf;
  conf.screen_width = 1640;
  conf.screen_height = 924;

  std::shared_ptr<adv::Scene> scene = std::make_shared<Editor>();
  WorldEdit game(conf, scene);

  game.run();

  return 0;
}
