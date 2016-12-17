#include <utility>
using std::pair;
using std::make_pair;

typedef pair<int, int> ii;
#define ALL_COOPERATE -1 // -1 in bits is all 1's

class PayoffMatrix {
public:
    PayoffMatrix();

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
    ii cc = make_pair(3, 3);
    ii cd = make_pair(0, 5);
    ii dc = make_pair(5, 0);
    ii dd = make_pair(1, 1);
};

class Player {
public:
    Player() : moves(0), fitness(0), history(ALL_COOPERATE) {}
    Player(int moves) : moves(moves), fitness(0), history(ALL_COOPERATE) {}

    int make_move(Player other_player) {
        return ((1 << other_player.history) & this->moves);
    }

    int moves;
    int fitness;
    int history;
};

class PD {
	public:
		PD();
		PD(Player _a, Player _b, PayoffMatrix _p) : a(_a), b(_b), pmat(_p) {}

		ii simulate(){
			int action_a = a.make_move(b);
			int action_b = b.make_move(a);
			return pmat.get_payoff(action_a,action_b);
		}

		PayoffMatrix pmat;
		Player a, b;

};
