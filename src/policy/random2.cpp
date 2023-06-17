#include <cstdlib>
#include <set>
#include<iostream>
#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

struct bundle
{
  bundle(Move m, int g):move(m), grade(g){}
  Move move;
  int grade;
};

struct cmp
{
  bool operator()(const bundle& a, const bundle& b)
  {
    return a.grade < b.grade;
  }
};

std::set<bundle, cmp> move_priority;

Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  for(auto action : state->legal_actions)
  {
    move_priority.emplace(action, state->next_state(action)->evaluate());
  }
  
  return move_priority.begin()->move;
}