#include "core/game.hpp"

using namespace adv;

Game::Game(Config conf) : 
  conf(conf), current_scene(conf.title)
{
}

void Game::run(void)
{
  while (true)
  {
    auto current_frame = chrono::duration_cast<chrono::milliseconds>(
      chrono::system_clock::now().time_since_epoch()
    );

    long delta = (current_frame - last_frame).count();

    long sleep_for = (1000 / conf.frames_per_second) - delta;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));

    update(delta);
    render(delta);

    last_frame = current_frame;
  }
}

void Game::update(long delta)
{
  current_scene.update(delta);
}

void Game::render(long delta)
{
  display.render_scene(current_scene, delta);
}

Scene Game::scene()
{
  return current_scene;
}

void Game::add_scene(Scene scene)
{
  scene_map[scene.name()] = scene;
}

void Game::set_scene(std::string name)
{
  current_scene = scene_map[name];
}