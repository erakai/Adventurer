#pragma once

#include "utils/color.hpp"
#include "utils/point.hpp"
#include "utils/Rect.hpp"
#include "SDL_Render.h"

#include <string>
#include <memory>
#include <map>

namespace adv
{

class Texture
{
  public:
    Texture(std::string name);

    void render(SDL_Renderer* renderer, Point display_pos, std::string sprite = "none");
  
    bool load_from_file(std::string file_path);
    void set_color(Color c);

    bool register_sprite(std::string name, Rect src_rect);

    std::string get_name();
    int get_width();
    int get_height();

  public:
    std::shared_ptr<SDL_Texture> texture;

    std::unordered_map<std::string, Rect> sprites;

    std::string name;
    int width;
    int height;
  
};

}