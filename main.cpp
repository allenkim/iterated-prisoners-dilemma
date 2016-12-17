#include <iostream>
#include <utility>
#include "pd.h"

using namespace std;

typedef pair<int,int> ii;

#define ALL_COOPERATE ((1<<16) - 1) // all 1's
#define ALL_DEFECT 0

int main(){
	PayoffMatrix pmat;
	Player allen(ALL_COOPERATE);
	Player porrith(ALL_DEFECT);

	// Tit for Tat - initially cooperate
	// if enemy defects, you defect
	// if enemy cooperates, you cooperate
	Player tit_for_tat(0b1010101010101010);
	PD game1(&allen,&tit_for_tat,&pmat);
	ii results1 = game1.simulate(100);
	cout << results1.first << " " << results1.second << endl;
	PD game2(&porrith,&tit_for_tat,&pmat);
	ii results2 = game2.simulate(100);
	cout << results2.first << " " << results2.second << endl;

	return 0;
}
