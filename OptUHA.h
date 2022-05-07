#pragma once
#ifndef _OPTUHA_
#define _OPTUHA_
#include <vector>
#include <random>
#include "iostream"
#include "solution.h"
using namespace std;


class OptUHA{
protected:
	int								pop_size;
	int								dimension;
	int								total_func_evals;
	int								max_func_eval = total_func_evals * pop_size; // nombre total d'appel de la fonction objectif
	bool								optimization_mode = 0; // 0 = min; 1 = max;
	vector<double>						bound_min;
	vector<double>						bound_max;
	OptUHA(int nbPop, int dim, int nbIter, vector<double> lower, vector<double> upper);
protected:
	vector<double>						d_fitness;

protected:
	vector<solution> GenerateRandomPop();
	double generate_random_double();
	int generate_random_int(int from, int to);
	solution create_new_individual();
	void print_solution(solution indv, double fitness);
	solution GenerateNewSolution(int current_ind_idx);
	void check_bound_sol(solution& s);

};

#endif
