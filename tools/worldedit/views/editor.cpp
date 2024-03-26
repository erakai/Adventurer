#include "editor.hpp"
#include "../components/tiler.hpp"
#include "../components/tool_selector.hpp"
#include "core/scene_resource.hpp"

Editor::Editor(std::shared_ptr<SceneResource> res)
    : adv::Scene("World Edit", {{1640, 924}}, res)
{
  std::shared_ptr<Tiler> new_tiler =
      std::shared_ptr<Tiler>(new Tiler({64 * 50, 64 * 50}));
  tiler = new_tiler;
  add_child(new_tiler);

  std::function<void(Tool)> set_tool = [this](Tool t) { tiler->set_tool(t); };
  std::shared_ptr<ToolSelector> ts =
      std::shared_ptr<ToolSelector>(new ToolSelector(set_tool));
  add_child(ts);
};

std::shared_ptr<Tiler> Editor::get_tiler()
{
  return tiler;
}
