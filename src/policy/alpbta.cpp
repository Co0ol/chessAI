#include <cstdlib>
#include<climits>
#include<algorithm>
#include <set>
#include<utility>
#include<iostream>
#include "../state/state.hpp"
#include "./alpbta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int alphabetaRec(State* s, int depth, int me, int alpha, int beta)
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
			val = std::max(val, alphabetaRec(s->next_state(i), depth-1, me, alpha, beta));
			alpha = std::max(alpha, val);
			if(alpha >= beta) break;
		}
	}
	else
	{
		val = INT_MAX;
		for(auto i : s->legal_actions)
		{
			val = std::min(val, alphabetaRec(s->next_state(i), depth-1, me, alpha, beta));
			beta = std::min(beta, val);
			if(alpha <= beta) break;
		}
	}
	return val;
}

Move alpbta::get_move(State *state, int depth){
	if(!state->legal_actions.size())
		state->get_legal_actions();
	
	auto actions = state->legal_actions;
	Move ans;
	int val;
	for(auto action : actions)
	{
		val = INT_MIN;
		int tmp = std::max(val, alphabetaRec(state->next_state(action), 8, state->player, INT_MIN, INT_MAX));
		if(val < tmp)
		{
			val = tmp;
			ans = action;
		}
	}
	return ans;
}