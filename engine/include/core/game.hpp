#pragma once

#include "updatable.hpp"
#include "config.hpp"
#include "scene.hpp"
#include "display/display.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <map>

using namespace std;

namespace adv
{

class Game: public Updatable
{
  public:
    Game(Config conf);

    void run(void);
    void update(long delta) override;
    void render(long delta) override;

    Scene scene();
    void add_scene(Scene scene);
    void set_scene(std::string name);

  private:
    // Config (globals) for the game
    Config conf;

    // Time since epoch in ms of last frame
    chrono::milliseconds last_frame;

    // Control actually rendering and display
    Display display;

    // Current scene that is being shown and needs updating
    Scene current_scene; 

    // Map of all scenes in the game
    std::map<std::string, Scene> scene_map;
};

};