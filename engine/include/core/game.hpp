#pragma once

#include "config.hpp"
#include "display/camera.hpp"
#include "display/display.hpp"
#include "scene.hpp"

#include <chrono>
#include <map>

using namespace std;

namespace adv
{

// :(
extern std::shared_ptr<Scene> CURRENT_SCENE;

class Game
{
public:
  Game(Config conf, std::shared_ptr<Scene> first_scene);

  void run(void);
  void update(long delta);
  void render(long delta);
  void close();

  int fps();
  std::shared_ptr<Scene> scene();
  Display &get_display();
  void add_scene(std::shared_ptr<Scene> scene);
  void set_scene(std::string name);

  void set_camera(std::shared_ptr<Camera> cam);

private:
  // Controls game loop
  bool running;

  // Config (globals) for the game
  Config conf;

  // Time since epoch in ms of last frame
  chrono::milliseconds last_frame;

  // Control actually rendering and display
  Display display;
  std::shared_ptr<Camera> camera;

  // Map of all scenes in the game
  std::map<std::string, std::shared_ptr<Scene>> scene_map;

  // Frames per second
  int frames_per_second = 0;
  long ms_counter = 0;
  int frames_in_last_second = 0;
};

}; // namespace adv
