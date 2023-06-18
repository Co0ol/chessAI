#include <cstdlib>
#include<climits>
#include<queue>
#include<fstream>
#include<string>
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

bool repeatMove(const Move& a, const Move& b)
{
	if(a.first.first == b.second.first
	&& a.first.second == b.second.second
	&& a.second.first == b.first.first
	&& a.second.second == b.first.second) return 1;
	else return 0;
}

Move alpbta::get_move(State *state, int depth){
	//avoid repeating
	std::vector<Move> previous;
	std::ifstream file("prevoius.log");
	if (file) {
		std::string str;
		while(std::getline(file, str))
		{
			Move tmp;
			tmp.first.first = str[0] - '0';
			tmp.first.second = str[1] - '0';
			tmp.second.first = str[3] - '0';
			tmp.second.second = str[4] - '0';
			previous.push_back(tmp);
		}
	}file.close();
	
	if(!state->legal_actions.size()) state->get_legal_actions();
	
	auto actions = state->legal_actions;
	Move ans = *(actions.begin());
	int val = INT_MIN;
	for(auto action : actions)
	{
		int tmp = alphabetaRec(state->next_state(action), depth-1, state->player, val, INT_MAX);
		if(val < tmp)
		{
			int noSame = 1;
			for(auto i : previous)
				if(repeatMove(action, i))
				{
					noSame = 0;
					break;
				}
			if(noSame)
			{
				val = tmp;
				ans = action;
			}
		}
	}
	previous.push_back(ans);
	if(previous.size() > 3)previous.erase(previous.begin());
	std::ofstream write;
	write.open("prevoius.log", std::ios::out | std::ios::trunc);
	for(auto i : previous)
		write << i.first.first << i.first.second << " " 
		<< i.second.first << i.second.second << std::endl;
	write.close();
	return ans;
}