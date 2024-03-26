#include "core/config.hpp"
#include "core/input.hpp"
#include "editor_resource.hpp"
#include "views/editor.hpp"
#include "worldedit.hpp"

#include "SDL.h"

int main(int argv, char **args)
{
  adv::Config conf;
  conf.title = "World Editor";
  conf.screen_width = 1640;
  conf.screen_height = 924;

  input::YIELD_TO_IMGUI = false;

  std::shared_ptr<Editor> scene =
      std::shared_ptr<Editor>(new Editor(std::make_shared<EditorResource>()));
  WorldEdit game(conf, scene);

  game.run();

  return 0;
}
