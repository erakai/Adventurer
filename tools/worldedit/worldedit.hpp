#pragma once

#include "core/game.hpp"

enum class State
{
  MAIN_MENU,
  EDITING,
  SAVING
};

class WorldEdit : public adv::Game
{
public:
  WorldEdit();

  void state_update(State new_state);

private:
  State state = State::MAIN_MENU;
};
