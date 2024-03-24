#include "editor.hpp"
#include "../components/tiler.hpp"

Editor::Editor() : adv::Scene("World Edit", {{1640, 924}})
{
  std::shared_ptr<Tiler> new_tiler = std::shared_ptr<Tiler>(new Tiler({0, 0}));
  tiler = new_tiler;
  add_child(new_tiler);
};
