#include "core/game.hpp"
#include "core/input.hpp"
#include "utils/logger.hpp"

#include <memory>
#include <thread>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

using namespace adv;

std::shared_ptr<Scene> adv::CURRENT_SCENE;

Game::Game(Config conf, std::shared_ptr<Scene> first_scene)
    : conf(conf),
      display(conf.screen_width, conf.screen_height, conf.title, conf.bg_color)
{
  add_scene(first_scene);
  set_scene(first_scene->name());
}

void Game::run(void)
{
  if (!display.is_initialized())
  {
    logger::log("Cannot run game - display not initialized.");
    close();
    return;
  }

  last_frame = chrono::duration_cast<chrono::milliseconds>(
      chrono::system_clock::now().time_since_epoch());

  logger::log("Beginning game loop...");
  running = true;
  while (running)
  {
    auto current_frame = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch());

    long delta = (current_frame - last_frame).count();
    long sleep_for = (1000 / conf.frames_per_second) - delta;

    if (sleep_for > 0 && conf.frames_per_second != -1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
      delta += sleep_for;
    }

    ms_counter += delta;
    frames_in_last_second += 1;
    if (ms_counter >= 1000)
    {
      ms_counter = ms_counter - 1000;
      frames_per_second = frames_in_last_second;
      frames_in_last_second = 0;
      if (globals::PRINT_FPS_DEBUG)
        logger::log("FPS: " + std::to_string(frames_per_second));
    }

    update(delta);

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    render(delta);

    last_frame = current_frame;
  }

  close();
}

void Game::close()
{
  logger::log("Shutting down...");
  display.close();
}

void Game::update(long delta)
{
  running = input::poll_event_loop();

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow();

  CURRENT_SCENE->update(delta);
}

void Game::render(long delta)
{
  if (camera == nullptr)
  {
    display.render_scene(CURRENT_SCENE, delta,
                         Rect(0, 0, conf.screen_width, conf.screen_height));
  }
  else
  {
    display.render_scene(CURRENT_SCENE, delta, camera->get_viewport());
  }
}

int Game::fps()
{
  return frames_per_second;
}

std::shared_ptr<Scene> Game::scene()
{
  return CURRENT_SCENE;
}

void Game::add_scene(std::shared_ptr<Scene> scene)
{
  scene_map[scene->name()] = scene;
}

void Game::set_scene(std::string name)
{
  if (scene_map.find(name) != scene_map.end())
  {
    logger::log("Changed scene to: \"" + name + "\"");
    CURRENT_SCENE = scene_map[name];
    CURRENT_SCENE->load_resources(display.get_renderer());
  }
  else
  {
    logger::log("Invalid scene: " + name);
  }
}

void Game::set_camera(std::shared_ptr<Camera> cam)
{
  camera = cam;
  input::add_camera(cam);
}
