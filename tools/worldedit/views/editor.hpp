#pragma once

#include "../components/tiler.hpp"
#include "core/scene.hpp"

class Editor : public adv::Scene
{
public:
  Editor();

  std::shared_ptr<Tiler> get_tiler();

private:
  std::shared_ptr<Tiler> tiler;
};
