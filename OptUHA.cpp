#include "OptUHA.h"
#include <random>
#include "iostream"
#include "solution.h"


using namespace std;


OptUHA::OptUHA(int nbPop, int dim, int nbIter, vector<double> lower, vector<double> upper)
    : pop_size{nbPop}, dimension{dim}, total_func_evals{nbIter}, max_func_eval{total_func_evals * pop_size},
    bound_min{lower}, bound_max{upper}
{}

vector<solution> OptUHA::GenerateRandomPop()
{
    vector<solution> populations{};
    populations.resize(pop_size);
    for(int i=0; i<pop_size; ++i){
        populations[i]=create_new_individual();
    }
    return populations;
}

double OptUHA::generate_random_double()
{

    return rand()*1.0/RAND_MAX;
}

int OptUHA::generate_random_int(int from, int to)
{
    return rand()%(to-from)+from;
}

solution OptUHA::create_new_individual()
{
    solution ind{};
    for(int i=0; i<dimension; ++i){
        double val=bound_min[i]+generate_random_double()*(bound_max[i]-bound_min[i]);
        ind.ajoutValeur(val);
    }
    return ind;
}

void OptUHA::print_solution(solution indv, double fitness)
{
    indv.printSolution();
    cout<<" Fitness : "<<fitness;
}

solution OptUHA::GenerateNewSolution(int current_ind_idx)
{
    solution newSolution{};
    return newSolution;
}

void OptUHA::check_bound_sol(solution& s)
{
    for(int j=0; j<dimension; ++j){
        if(s.valeur(j)>bound_max[j]){
            s.changeValeur(bound_max[j], j);
        }
        else if(s.valeur(j)<bound_min[j]){
            s.changeValeur(bound_min[j], j);
        }
    }
}

