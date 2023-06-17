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
	if(depth == 0) return s->evaluate(me);
	
	if(!s->legal_actions.size())
		s->get_legal_actions();

	if(s->player == me)
	{
		for(auto i : s->legal_actions)
		{
			alpha = std::max(alpha, alphabetaRec(s->next_state(i), depth-1, me, alpha, INT_MAX));
			if(alpha >= beta) break;
		}
		return alpha;
	}
	else
	{
		for(auto i : s->legal_actions)
		{
			beta = std::min(beta, alphabetaRec(s->next_state(i), depth-1, me, INT_MIN, beta));
			if(alpha >= beta) break;
		}
		return beta;
	}
}

Move alpbta::get_move(State *state, int depth){
	if(!state->legal_actions.size())
		state->get_legal_actions();
	
	auto actions = state->legal_actions;
	Move ans = *(actions.begin());
	int val = INT_MIN;
	for(auto action : actions)
	{
		int tmp = alphabetaRec(state->next_state(action), depth-1, state->player, val, INT_MAX);
		if(val < tmp)
		{
			val = tmp;
			ans = action;
		}
	}
	return ans;
}