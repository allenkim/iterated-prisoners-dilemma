#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "pd.h"

using namespace std;

typedef pair<int,int> ii;

#define ALL_COOPERATE ((1<<16) - 1) // all 1's
#define ALL_DEFECT 0

int main(){
	// Initialize random seed
	srand(time(NULL));

	PayoffMatrix pmat;
	// Tit for Tat - initially cooperate
	// if enemy defects, you defect
	// if enemy cooperates, you cooperate
	Player tit_for_tat(0b1010101010101010);

	// Initialize population
	const int POPULATION = 100;
	vector<Player> players;
	for (int i = 0; i < POPULATION; i++){
		players.push_back(Player(rand() % (1<<16)));
	}

	// Evaluate fitnesses of population
	for (int i = 0; i < POPULATION; i++){
		for (int j = i+1; j < POPULATION; j++){
			PD game(&players[i],&players[j],&pmat);
			int NUM_ROUNDS = rand() % 200 + 1;
			ii results = game.simulate(NUM_ROUNDS);
			int sum = results.first + results.second;
			players[i].fitness += sum;
			players[j].fitness += sum;
		}
	}

	// Selection
	sort(players.begin(), players.end());
	vector<int> surviving_pop;
	const int SURVIVING_NUMBER = 20;
	for (int i = POPULATION - 1; i >= POPULATION - 1 - SURVIVING_NUMBER; i--){
		cout << players[i].fitness << endl;
	}
	

	return 0;
}
