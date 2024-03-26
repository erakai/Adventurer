#include "tool_selector.hpp"
#include "core/game.hpp"
#include "display/ui_node.hpp"
#include "imgui.h"

using namespace adv;

ToolSelector::ToolSelector(std::function<void(Tool k)> st)
    : UINode({10, 10}, {53, 350})
{
  set_tool = st;
}

void ToolSelector::render_self(SDL_Renderer *renderer)
{
  set_imgui_window();

  ImGui::Begin("##Tools");
  if (ImGui::ImageButton("##Pan",
                         adv::CURRENT_SCENE->res()->textures["mouse"].texture,
                         {30, 30}))
    set_tool(Tool::PAN);
  if (ImGui::ImageButton("##Place",
                         adv::CURRENT_SCENE->res()->textures["box"].texture,
                         {30, 30}))
    set_tool(Tool::PLACE);
  ImGui::End();
}
