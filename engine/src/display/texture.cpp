#include "display/texture.hpp"
#include "SDL_image.h"
#include "SDL_render.h"
#include "utils/logger.hpp"
#include "utils/rect.hpp"

using namespace adv;

Texture::Texture(SDL_Renderer *renderer, std::string fp) : filepath(fp)
{
  load_from_file(renderer, fp);
}

void Texture::close()
{
  SDL_DestroyTexture(texture);
  texture = nullptr;
}

void Texture::render(SDL_Renderer *renderer, Rect display_rect,
                     std::string sprite)
{
  if (!is_loaded())
  {
    logger::log("Texture not loaded on render call: \"" + filepath + "\"");
    return;
  }

  if (sprite == "none")
  {
    SDL_Rect destination = {display_rect.x1(), display_rect.y1(),
                            display_rect.width(), display_rect.height()};

    if (SDL_RenderCopy(renderer, texture, nullptr, &destination) < 0)
    {
      logger::log_sdl("Error rendering texture: \"" + filepath + "\"");
    }
  }
  else
  {
    render(renderer, display_rect, sprites[sprite]);
  }
}

void Texture::render(SDL_Renderer *renderer, Rect display_rect, SDL_Rect clip)
{
  if (!is_loaded())
  {
    logger::log("Texture not loaded on render call...");
    return;
  }

  SDL_Rect destination = {display_rect.x1(), display_rect.y1(),
                          display_rect.width(), display_rect.height()};
  if (SDL_RenderCopy(renderer, texture, &clip, &destination) < 0)
  {
    logger::log_sdl("Error rendering texture: \"" + filepath + "\"");
  }
}

bool Texture::load_from_file(SDL_Renderer *renderer, std::string file_path)
{
  if (is_loaded() && texture != nullptr)
  {
    return true;
  }

  texture = IMG_LoadTexture(renderer, file_path.c_str());
  if (texture == nullptr)
  {
    logger::log_sdl("Failed to load texture: \"" + file_path + "\"");
    return false;
  }

  filepath = file_path;
  loaded = true;

  return true;
}

void Texture::set_color(Color c)
{
  SDL_SetTextureColorMod(texture, c.r, c.g, c.b);
  if (c.opacity != 0xFF)
  {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, c.opacity);
  }
}

bool Texture::register_sprite(std::string name, SDL_Rect src_rect)
{
  if (name == "none")
    return false;

  sprites[name] = src_rect;
  return true;
}

bool Texture::is_loaded()
{
  return loaded;
}

std::string Texture::get_filepath()
{
  return filepath;
}

SDL_Texture *Texture::get_texture()
{
  return texture;
}
