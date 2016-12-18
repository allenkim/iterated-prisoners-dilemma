#include <utility>
#include "pd.h"

using std::pair;
using std::make_pair;

typedef pair<int, int> ii;
#define ALL_COOPERATE_HISTORY ((1 << 4) - 1)

// PayoffMatrix implementation
PayoffMatrix::PayoffMatrix()
{
    cc = make_pair(3, 3);
    cd = make_pair(0, 5);
    dc = make_pair(5, 0);
    dd = make_pair(1, 1);
}

ii PayoffMatrix::get_payoff(int first_action, int second_action) {
    if (first_action == 0 && second_action == 0)
		return this->dd;
	else if (first_action == 0 && second_action == 1)
		return this->dc;
	else if (first_action == 1 && second_action == 0)
		return this->cd;
	else
		return this->cc;
}

// Player implementation
Player::Player() : moves(0), fitness(0), history(ALL_COOPERATE_HISTORY) {}

Player::Player(int _moves) : moves(_moves), fitness(0), history(ALL_COOPERATE_HISTORY) {}

int Player::make_move(Player* other_player) {
    int move = ((1 << (other_player->history)) & this->moves) != 0;
    return move;
}

bool Player::operator<(const Player& rhs) const {
    return this->fitness < rhs.fitness;
}

// Prisoner's Dilemma Function implementations
PD::PD() : a(0), b(0), pmat() {}

PD::PD(Player* _a, Player* _b, PayoffMatrix* _p) : a(_a), b(_b), pmat(_p) {}

ii PD::simulate(int n) {
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
