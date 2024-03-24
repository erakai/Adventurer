#include "debug/globaldebug.hpp"
#include "core/input.hpp"
#include "display/ui_node.hpp"
#include "utils/globals.hpp"

#include "SDL_render.h"
#include "imgui.h"

using namespace adv;

GlobalDebugWindow::GlobalDebugWindow() : UINode({10, 10}, {200, 300})
{
  std::function<void()> release = [this]() { handle_debug_release(); };
  input::key_hook(input::DEBUG_RELEASE, release);
}

void GlobalDebugWindow::handle_debug_release()
{
  visible = !visible;
}

void GlobalDebugWindow::render_self(SDL_Renderer *renderer)
{
  if (!visible)
    return;

  set_imgui_window();

  ImGui::Begin("Globals Debug");
  ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
              ImGui::GetIO().Framerate);
  ImGui::Spacing();
  ImGui::Text("Max FPS");
  ImGui::SliderInt("##fps", &globals::FPS, -1, 500);
  ImGui::Spacing();
  ImGui::Checkbox("Show Colliders", &globals::COLLISION_DEBUG);
  ImGui::Checkbox("Print FPS", &globals::PRINT_FPS_DEBUG);
  ImGui::NewLine();
  ImGui::Text("Render Distance");
  ImGui::SliderInt("##render", &globals::CHUNK_RENDER_DISTANCE, 1, 30);
  ImGui::End();
}
