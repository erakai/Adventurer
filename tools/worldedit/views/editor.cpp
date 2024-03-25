#include "editor.hpp"
#include "../components/tiler.hpp"
#include "core/scene_resource.hpp"

Editor::Editor()
    : adv::Scene("World Edit", {{1640, 924}}, std::make_shared<SceneResource>())
{
  std::shared_ptr<Tiler> new_tiler =
      std::shared_ptr<Tiler>(new Tiler({64 * 50, 64 * 50}));
  tiler = new_tiler;
  add_child(new_tiler);
};

std::shared_ptr<Tiler> Editor::get_tiler()
{
  return tiler;
}
