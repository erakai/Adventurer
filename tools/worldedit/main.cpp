#include "core/config.hpp"
#include "views/editor.hpp"
#include "worldedit.hpp"

int main(int argv, char **args)
{
  adv::Config conf;
  conf.screen_width = 1640;
  conf.screen_height = 924;

  std::shared_ptr<Editor> scene = std::make_shared<Editor>();
  WorldEdit game(conf, scene);

  auto &textures = scene->res()->textures;
  textures["tiles"] = Texture(game.get_display().get_renderer(),
                              "assets/RF_Catacombs_v1.0/mainlevbuild.png");
  textures["tiles"].register_sprite("floor", {832, 224, 16, 16});
  scene->get_tiler()->set_selected_tile({"tiles", "floor", false, true});

  game.run();

  return 0;
}
