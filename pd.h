#pragma once

#include <cstdio>
#include <iostream>
#include <bitset>
#include <utility>
using std::pair;
using std::make_pair;

typedef pair<int, int> ii;
#define ALL_COOPERATE_HISTORY ((1<<4) - 1) // 1111

class PayoffMatrix {
	public:
		PayoffMatrix() {}

		ii cc = make_pair(3, 3);
		ii cd = make_pair(0, 5);
		ii dc = make_pair(5, 0);
		ii dd = make_pair(1, 1);

		// For action, 0 is defect and 1 is cooperate
		ii get_payoff(int first_action, int second_action) {
			if (first_action == 0 && second_action == 0)
				return dd;
			else if (first_action == 0 && second_action == 1)
				return dc;
			else if (first_action == 1 && second_action == 0)
				return cd;
			else
				return cc;
		} 
}; 

class Player {
	public:
		Player() : moves(0), fitness(0), history(ALL_COOPERATE_HISTORY) {}
		Player(int _moves) : moves(_moves), fitness(0), history(ALL_COOPERATE_HISTORY) {}

		int moves;
		int fitness;
		int history;

		// Based off of other person's history, make a move
		// moves -> 16 least significant bits to consider
		// history is only 4 least significant bits (0 to 15)
		int make_move(Player* other_player) {
			int move = ((1 << (other_player->history)) & this->moves) != 0;
//			std::cout << move << " ";
//			std::bitset<16> bs(this->moves);
//			std::cout << bs << std::endl;
			return move;
		}
		bool operator<(const Player& rhs) const {
			return this->fitness < rhs.fitness;
		}
};

class PD {
	public:
		PD() : a(0), b(0), pmat() {}
		PD(Player* _a, Player* _b, PayoffMatrix* _p) : a(_a), b(_b), pmat(_p) {}

		Player* a;
		Player* b;
		PayoffMatrix* pmat;

		ii simulate(int n = 1){
			ii total_results = make_pair(0,0);
			for (int i = 0; i < n; i++){
				int action_a = a->make_move(b);
				int action_b = b->make_move(a);
				ii result = pmat->get_payoff(action_a,action_b);
				a->history = a->history << 1;
				a->history &= 15;
				a->history |= action_a;
				b->history = b->history << 1;
				b->history &= 15;
				b->history |= action_b;
				total_results.first += result.first;
				total_results.second += result.second;
			}
			return total_results;
		}
};
