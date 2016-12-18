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
#define POP_SIZE 100

PayoffMatrix pmat;

size_t eval_fitness(vector<Player> &population){
	// Evaluate fitnesses of population
	int total_fitness = 0;
	for (int i = 0; i < POP_SIZE; i++){
		for (int j = i+1; j < POP_SIZE; j++){
			PD game(&population[i],&population[j],&pmat);
			int NUM_ROUNDS = rand() % 200 + 1;
			ii results = game.simulate(NUM_ROUNDS);
			int sum = results.first + results.second;
			population[i].fitness += sum;
			population[j].fitness += sum;
			total_fitness += 2 * sum;
		}
	}
	return total_fitness;
}

vector<Player*> selection(vector<Player> &population, size_t total_fitness){
	vector<Player*> surviving_pop;
	const int SURVIVING_NUMBER = rand() % (POP_SIZE/2 - POP_SIZE/5) + POP_SIZE/5;
	vector<double> roulette_wheel;
	roulette_wheel.push_back((double)population[0].fitness / total_fitness);
	for (int i = 1; i < POP_SIZE; i++){
		roulette_wheel.push_back(roulette_wheel[i-1] + (double)population[i].fitness / total_fitness);
	}
	for (int i = 0; i < SURVIVING_NUMBER; i++){
		double selector = (double)rand() / RAND_MAX;
		for (int j = 0; j < POP_SIZE; j++){
			if (selector < roulette_wheel[j]){				
				bool already_survived = false;
				for (size_t k = 0; k < surviving_pop.size(); k++){
					if (surviving_pop[k] == &population[j]){
						already_survived = true;
						break;
					}
				}
				if (!already_survived){
					surviving_pop.push_back(&population[j]);
					break;
				}
			}
		}
	}
	return surviving_pop;
}

vector<Player> crossover(vector<Player*> &surviving_pop){
	vector<Player> new_generation;
	size_t pop_size = surviving_pop.size();
	for (int i = 0; i < POP_SIZE; i++){
		Player* mate1 = surviving_pop[rand() % pop_size];
		Player* mate2 = surviving_pop[rand() % pop_size];
		int partition = rand() % 16;
		int child_moves = mate2->moves;
		int mask = (1 << partition) - 1;
		child_moves &= mask;
		child_moves |= (mate1->moves & (~mask));
		new_generation.push_back(Player(child_moves));
	}
	return new_generation;
}

int mutation(vector<Player> &population){
	// 1 / MUTATE_CHANCE is probability
	int mutate_count = 0;
	size_t MUTATE_CHANCE = 100;
	for (int i = 0; i < POP_SIZE; i++){
		if (rand() % MUTATE_CHANCE == 1){
			mutate_count++;
			int bit = rand() % 16;
			population[i].moves ^= (1 << bit);
		}
	}
	return mutate_count;
}

vector<Player> next_gen(vector<Player> &population){
	size_t total_fitness = eval_fitness(population);
	cout << total_fitness;
	vector<Player*> selected = selection(population, total_fitness);
	vector<Player> new_gen = crossover(selected);
	mutation(new_gen);
	return new_gen;
	
}

void simulate(vector<Player> &init_pop, int num_gen){
	vector<Player> curr_pop(init_pop);
	for (int generation = 1; generation <= num_gen; generation++){
		cout << "Generation " << generation << ": ";
		curr_pop = next_gen(curr_pop);
		cout << endl;
	}
}

int main(){
	// Initialize random seed
	srand(time(NULL));

	// For reference
	// Tit for Tat - initially cooperate
	// if enemy defects, you defect
	// if enemy cooperates, you cooperate
	// Player tit_for_tat(0b1010101010101010);

	// Initialize population
	vector<Player> population;
	for (int i = 0; i < POP_SIZE; i++){
		population.push_back(Player(rand() % (1<<16)));
	}

	simulate(population, 100);

	// Initialize population
//	vector<Player> ult_pop;
//	for (int i = 0; i < POP_SIZE; i++){
//		ult_pop.push_back(Player(0b1010101010101010));
//	}

	//simulate(ult_pop, 100);


	return 0;
}
