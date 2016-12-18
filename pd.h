#pragma once

#include <cstdio>
#include <iostream>
#include <bitset>
#include <utility>
using std::pair;
using std::make_pair;

typedef pair<int, int> ii;

class PayoffMatrix {
	public:
		PayoffMatrix();

		ii cc;
		ii cd;
		ii dc;
		ii dd;

		// For action, 0 is defect and 1 is cooperate
		ii get_payoff(int first_action, int second_action);
};

class Player {
	public:
		Player();
		Player(int _moves);

		int moves;
		int fitness;
		int history;

		// Based off of other person's history, make a move
		// moves -> 16 least significant bits to consider
		// history is only 4 least significant bits (0 to 15)
		int make_move(Player* other_player);
		bool operator<(const Player& rhs) const;
};

class PD {
	public:
		PD();
		PD(Player* _a, Player* _b, PayoffMatrix* _p);

		Player* a;
		Player* b;
		PayoffMatrix* pmat;

		ii simulate(int n = 1);
};
