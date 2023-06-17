#include <cstdlib>
#include<climits>
#include<algorithm>
#include <set>
#include<utility>
#include<iostream>
#include "../state/state.hpp"
#include "./minmax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minmaxRec(State* s, int depth, int me)
{
	if(depth == 0) return s->evaluate();
	
	int val = 0;
	if(!s->legal_actions.size())
		s->get_legal_actions();
	if(s->player == me)
	{
		val = INT_MIN;
		for(auto i : s->legal_actions)
		{
			val = std::max(val, minmaxRec(s->next_state(i), depth-1, me));
		}
	}
	else
	{
		val = INT_MAX;
		for(auto i : s->legal_actions)
		{
			val = std::min(val, minmaxRec(s->next_state(i), depth-1, me));
		}
	}
	return val;
}

Move minmax::get_move(State *state, int depth){
	if(!state->legal_actions.size())
		state->get_legal_actions();
	
	auto actions = state->legal_actions;
	Move ans;
	int val;
	for(auto action : actions)
	{
		val = INT_MIN;
		int tmp = std::max(val, minmaxRec(state->next_state(action), 4, state->player));
		if(val < tmp)
		{
			val = tmp;
			ans = action;
		}
	}
	return ans;
}