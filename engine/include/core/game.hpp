#pragma once

#include "config.hpp"
#include "display/display.hpp"
#include "scene.hpp"

#include <chrono>
#include <map>

using namespace std;

namespace adv
{

class Game
{
public:
  Game(Config conf);

  void run(void);
  void update(long delta);
  void render(long delta);
  void close();

  int fps();
  std::shared_ptr<Scene> scene();
  void add_scene(std::shared_ptr<Scene> scene);
  void set_scene(std::string name);

private:
  // Controls game loop
  bool running;

  // Config (globals) for the game
  Config conf;

  // Time since epoch in ms of last frame
  chrono::milliseconds last_frame;

  // Control actually rendering and display
  Display display;

  // Current scene that is being shown and needs updating
  std::shared_ptr<Scene> current_scene;

  // Map of all scenes in the game
  std::map<std::string, std::shared_ptr<Scene>> scene_map;

  // Frames per second
  int frames_per_second = 0;
  long ms_counter = 0;
  int frames_in_last_second = 0;
};

}; // namespace adv
