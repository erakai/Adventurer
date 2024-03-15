#include "sidebar.hpp"
#include "utils/point.hpp"

#include "imgui.h"

using namespace adv;

Sidebar::Sidebar() : UINode(Point(1250, 10), {1640 - 1250 - 10, 924 - 10 - 10})
{
}

void Sidebar::render_self(SDL_Renderer *renderer)
{
  set_imgui_window();

  ImGui::Begin("Texture Selector");
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();
}
