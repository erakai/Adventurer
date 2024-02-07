#include "core/game.hpp"

using namespace adv;

Game::Game(Config conf) : 
  conf(conf), display(conf.screen_width, conf.screen_height, conf.title)
{
  current_scene = std::shared_ptr<Scene>(new Scene(conf.title));
}

void Game::run(void)
{
  if (!display.is_initialized())
  {
    logger::log("CANNOT RUN GAME - DISPLAY NOT INITIALIZED");
  }

  running = true;
  while (running)
  {
    auto current_frame = chrono::duration_cast<chrono::milliseconds>(
      chrono::system_clock::now().time_since_epoch()
    );

    long delta = (current_frame - last_frame).count();

    // TODO: Revisit frame timing logic
    // Potentially use SDL timer?
    long sleep_for = (1000 / conf.frames_per_second) - delta;
    if (sleep_for > 0) std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));

    update(delta);
    render(delta);

    last_frame = current_frame;
  }
}

void Game::update(long delta)
{
  current_scene->update(delta);
  running = input::poll_event_loop();
}

void Game::render(long delta)
{
  display.render_scene(current_scene, delta);
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