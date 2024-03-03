#include "core/game.hpp"
#include "core/input.hpp"
#include "utils/logger.hpp"

#include <thread>

using namespace adv;

Game::Game(Config conf)
    : conf(conf),
      display(conf.screen_width, conf.screen_height, conf.title, conf.bg_color)
{
  current_scene = std::make_shared<Scene>(
      conf.title,
      Rect(0, 0, conf.screen_width * globals::WORLD_DIST_PER_DISPLAY_PIXEL,
           conf.screen_height * globals::WORLD_DIST_PER_DISPLAY_PIXEL));
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
    render(delta);

    last_frame = current_frame;
  }

  close();
}

void Game::close()
{
  logger::log("Shutting down...");
}

void Game::update(long delta)
{
  running = input::poll_event_loop();
  current_scene->update(delta);
}

void Game::render(long delta)
{
  if (camera == nullptr)
  {
    display.render_scene(current_scene, delta,
                        Rect(0, 0, conf.screen_width, conf.screen_height));
  }
  else
  {
    display.render_scene(current_scene, delta, camera->get_viewport());
  }
}

int Game::fps()
{
  return frames_per_second;
}

std::shared_ptr<Scene> Game::scene()
{
  return current_scene;
}

void Game::add_scene(std::shared_ptr<Scene> scene)
{
  scene_map[scene->name()] = scene;
}

void Game::set_scene(std::string name)
{
  if (scene_map.find(name) != scene_map.end())
  {
    current_scene = scene_map[name];
  }
  else
  {
    logger::log("Invalid scene: " + name);
  }
}

void Game::set_camera(std::shared_ptr<Camera> cam)
{
  camera = cam;
}