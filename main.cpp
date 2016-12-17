#include <iostream>
#include <utility>
#include "pd.h"

using namespace std;

typedef pair<int,int> ii;

int main(){
	PayoffMatrix pmat;
	Player allen(0);
	Player porrith(0);
	PD game(allen,porrith,pmat);
	ii results = game.simulate();
	cout << results.first << " " << results.second << endl;

	return 0;
}
