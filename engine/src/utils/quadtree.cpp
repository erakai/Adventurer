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

void QuadTree::insert(std::shared_ptr<GameObject> obj)
{
  if (has_split)
  {
    int index = get_index(*obj);
    if (index != -1)
    {
      nodes[index]->insert(obj);
    }

    return;
  }

  if (objects.size() + 1 < globals::MAX_OBJECTS_PER_QUADTREE_NODE)
  {
    objects.push_back(obj);
  }
  else if (level < globals::MAX_QUADTREE_LEVELS)
  {
    split();
    for (auto &obj: objects)
    {
      int index = get_index(*obj);
      if (index != -1) nodes[index]->insert(obj);
    }
    objects.clear();
  }
  else
  {
    logger::log("Could not add game object to QuadTree - maximum depth exceeded");
  }
}

int QuadTree::get_index(GameObject obj)
{
  int index = -1;
  int ox = obj.pos().x();
  int oy = obj.pos().y();

  bool top_quad = (oy < bounds.center_y());

  if (ox < bounds.center_x())
  {
    if (top_quad) index = 0;
    else index = 1;
  }
  else
  {
    if (top_quad) index = 1;
    else index = 3;
  }

  return index;
}

std::vector<std::shared_ptr<GameObject>> QuadTree::retrieve_nearby(
  const GameObject obj)
{
  std::vector<std::shared_ptr<GameObject>> return_objs;
  retrieve(return_objs, obj);
  return return_objs;
}

void QuadTree::retrieve(
  std::vector<std::shared_ptr<GameObject>> &return_objs,
  GameObject obj)
{
  int index = get_index(obj);
  if (index != -1 && has_split)
  {
    nodes[index]->retrieve(return_objs, obj);
  }

  return_objs.insert(return_objs.end(), objects.begin(), objects.end());
}


