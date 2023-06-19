#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
//static Move previous;

class submission{
public:
  static Move get_move(State *state, int depth);
};