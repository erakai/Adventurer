#pragma once

#include "utils/rect.hpp"
#include "SDL_render.h"

#include <algorithm>
#include <vector>
#include <memory>

namespace adv
{

class Node
{
  public:
    virtual ~Node() {}
    virtual void update(long delta) {}
    virtual void render(SDL_Renderer* renderer, long delta, Rect viewport) {}

    void update_children(long delta);
    void render_children(SDL_Renderer* renderer, long delta, Rect viewport);
    void add_child(std::shared_ptr<Node> n);
    void remove_child(std::shared_ptr<Node> n);

    void kill();
    bool is_marked_for_death();
  
  private:
    std::vector<std::shared_ptr<Node>> children;

    bool marked_for_death;
};

};