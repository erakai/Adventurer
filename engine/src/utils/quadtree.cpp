#include "utils/quadtree.hpp"

using namespace adv;

void QuadTree::clear()
{
  objects.clear();

  if (has_split)
  {
    for (auto &n: nodes)
    {
      n->clear();
      n = nullptr;
    }
  }

  has_split = false;
}

void QuadTree::split()
{
  if (has_split) return;

  int new_width = bounds.width() / 2;
  int new_height = bounds.height() / 2;
  int x = bounds.x1();
  int y = bounds.y1();

  nodes[0] = std::make_shared<QuadTree>(level + 1,
    Rect(x , y, x + new_width, y + new_height
  )); // TL
  nodes[1] = std::make_shared<QuadTree>(level + 1,
    Rect(x + new_width, y, x + new_width + new_width, y + new_height
  )); // TR
  nodes[2] = std::make_shared<QuadTree>(level + 1,
    Rect(x, y + new_height, x + new_width, y + new_height + new_height
  )); // BL
  nodes[3] = std::make_shared<QuadTree>(level + 1,
    Rect(x + new_width, y + new_height, x + new_width + new_width, y + new_height + new_height
  )); // BR

  has_split = true;
}

void QuadTree::insert(std::shared_ptr<Positioned> obj)
{
  if (has_split)
  {
    int index = get_index(*obj);
    if (index != -1)
    {
      nodes[index]->insert(obj);
      return;
    }
  }

  objects.push_back(obj);

  if ((objects.size() > globals::MAX_OBJECTS_PER_QUADTREE_NODE) &&
      (level < globals::MAX_QUADTREE_LEVELS))
  {
    if (!has_split) split();

    std::size_t i = 0;
    while (i < objects.size())
    {
      auto obj = objects.at(i);
      int index = get_index(*obj);

      if (index != -1)
      {
        nodes[index]->insert(obj);
        objects.erase(objects.begin() + i);
      }
      else
      {
        i++;
      }
    }
  }
  else if ((objects.size() > globals::MAX_OBJECTS_PER_QUADTREE_NODE) && (level >= globals::MAX_QUADTREE_LEVELS))
  {
    logger::log("Forced to exceed maximum objects per QuadTree - level: " + std::to_string(level));
  }
}

int QuadTree::get_index(Positioned obj)
{
  int index = -1;
  int ox = obj.pos().x();
  int oy = obj.pos().y();

  bool top_quad = (oy < bounds.center_y()) &&
                  (oy + obj.size().height() < bounds.center_y());
  bool bottom_quad = (oy > bounds.center_y());

  if ((ox < bounds.center_x()) && (ox + obj.size().width() < bounds.center_x()))
  {
    if (top_quad) index = 0;
    else if (bottom_quad) index = 2;
  }
  else if (ox > bounds.center_x())
  {
    if (top_quad) index = 1;
    else if (bottom_quad) index = 3;
  }

  return index;
}

std::vector<std::shared_ptr<Positioned>> QuadTree::retrieve_nearby(
  const Positioned obj)
{
  std::vector<std::shared_ptr<Positioned>> return_objs;
  retrieve(return_objs, obj);
  return return_objs;
}

void QuadTree::retrieve(
  std::vector<std::shared_ptr<Positioned>> &return_objs,
  Positioned obj)
{
  int index = get_index(obj);

  if (index != -1 && has_split)
  {
    nodes[index]->retrieve(return_objs, obj);
  }
  else if (has_split)
  {
    for (auto &n: nodes) n->retrieve(return_objs, obj);
  }

  return_objs.insert(return_objs.end(), objects.begin(), objects.end());
}


