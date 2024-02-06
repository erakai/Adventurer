#pragma once

#include "node.hpp"
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

class Game: public Node
{
  public:
    Game(Config conf);

    void run(void);
    void update(long delta) override;
    void render(long delta) override;

    std::shared_ptr<Scene> scene();
    void add_scene(std::shared_ptr<Scene> scene);
    void set_scene(std::string name);

  private:
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