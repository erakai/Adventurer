#pragma once

#include "config.hpp"
#include "scene.hpp"
#include "input.hpp"
#include "node.hpp"
#include "display/display.hpp"
#include "utils/logger.hpp"

#include <iostream>
#include <chrono>
#include <thread>
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
};

};