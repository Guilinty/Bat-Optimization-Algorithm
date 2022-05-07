#include "myAlgorithm.h"
#include "OptUHA.h"
#include <cmath>
#include <vector>
#include <random>
#include <fstream>


myAlgorithm::myAlgorithm(int nbPop, int dim, int nbIter, vector<double> lower, vector<double> upper,
                          double fmin, double fmax, double Amin, double Amax, double rMin, double rMax, int func_num)
    : OptUHA{nbPop, dim, nbIter, lower, upper}, d_fMin{fmin}, d_fMax{fmax},d_aMin{Amin}, d_aMax{Amax}, d_rMin{rMin}, d_rMax{rMax}, d_func_num{func_num}
{
    d_population=GenerateRandomPop();
    d_velocity=velocityPop();
    d_frequency=randomValues(d_fMin, d_fMax);
    d_loudness=randomValues(Amin, Amax);
    d_pulseRate=randomValues(rMin, rMax);
    evaluate_pop(d_func_num, d_fitness);
    d_bestBat=FindBestSolution();
    int ind=IndexBestSolution();
    d_minFitness=d_fitness[ind];
}

solution myAlgorithm::FindBestSolution() const
{
    int minInd=0;
    for(int i=1; i<pop_size; ++i){
        if(d_fitness[i]<d_fitness[minInd])
            minInd=i;
    }
    return d_population[minInd];
}

int myAlgorithm::IndexBestSolution() const
{
    int minInd=0;
    for(int i=1; i<pop_size; ++i){
        if(d_fitness[i]<d_fitness[minInd])
            minInd=i;
    }
    return minInd;
}

void myAlgorithm::evaluate_pop(int num_func, vector<double>& fitness)
{
    fitness.resize(pop_size);
    for(int i=0; i<pop_size; ++i){
        fitness[i]=evaluate_individual(num_func, d_population[i]);
    }
}

double myAlgorithm::evaluate_individual(int funct_num, solution& ind) const
{
    double valFitness=ind.fonctionFitness(funct_num);

    return valFitness;
}

vector<solution> myAlgorithm::velocityPop()
{
    vector<solution> velocity;
    velocity.resize(pop_size);
    for(int i=0; i<pop_size; ++i){
        for(int j=0; j<dimension; ++j){
            velocity[i].ajoutValeur(0.0);
        }
    }
    return velocity;
}

vector<double> myAlgorithm::randomValues(double min, double max)
{
    vector<double> init;
    init.resize(pop_size);
    for(int i=0; i<pop_size; ++i){
        double valeur=generate_random_double()*(max-min);
        init[i]=valeur;
    }
    return init;
}

double myAlgorithm::meanOfbats(const vector<double> loudness) const
{
    double som{0.0};
    for(int i=0; i<pop_size; ++i){
        som+=loudness[i];
    }
    return som/pop_size;
}

void myAlgorithm::randomSolution(solution& s)
{
    for(int i=0; i<dimension; ++i){
        double alea=s.valeur(i);
        alea+=bound_min[i]+generate_random_double()*(bound_max[i]-bound_min[i]);
        s.changeValeur(alea, i);
    }
    check_bound_sol(s);
}

//ALGORITHME DE BAT OPTIMISATION

void myAlgorithm::BAT()
{
    solution newSol{};
    for(int j=0; j<dimension; ++j)
        newSol.ajoutValeur(0.0);
    vector<double>initPulseRate=d_pulseRate;
    //REMARQUE : beta fixe=>meilleur solution
    //double beta=0.0+generate_random_double()*(1.0-0.0);
    int iter=0;
    while(iter<total_func_evals)
    {
        for(int i=0; i<pop_size; ++i)
        {
            double beta=0.0+generate_random_double()*(1.0-0.0);
            d_frequency[i]=d_fMin+(d_fMax-d_fMin)*beta;
            for(int j=0; j<dimension; ++j){
                //MAJ Velocity
                double v=d_velocity[i].valeur(j);
                v+=(d_population[i].valeur(j)-d_bestBat.valeur(j))*d_frequency[i];
                d_velocity[i].changeValeur(v, j);
                //MAJ Position
                double p=d_population[i].valeur(j)+v;
                newSol.changeValeur(p, j);
                check_bound_sol(newSol);
            }
            double ran=d_rMin+generate_random_double()*(d_rMax-d_rMin);
            if(ran>d_pulseRate[i]){
                //generer une solution locale
                for(int j=0; j<dimension; ++j){
                    double epsilon=-1.0+generate_random_double()*(1.0+1.0);
                    double val=d_bestBat.valeur(j) + epsilon*meanOfbats(d_loudness);
                    newSol.changeValeur(val, j);
                    check_bound_sol(newSol);
                }
            }
            else{
                //Generer une solution aleatoire
                randomSolution(newSol);
            }
            //Fitness des nouvelles positions
            ran=d_aMin+generate_random_double()*(d_aMax-d_aMin);
            double newFitness=evaluate_individual(d_func_num, newSol);
            if(ran<d_loudness[i] && newFitness<d_fitness[i]){
                //Accepter la nouvelle solution
                for(int j=0; j<dimension; ++j){
                    d_population[i].changeValeur(newSol.valeur(j), j);
                }
                d_fitness[i]=newFitness;
                //Augmenter Ri et diminuer Ai
                d_loudness[i]=ALPHA*d_loudness[i];
                d_pulseRate[i]=initPulseRate[i]*(1-std::exp(-GAMMA*iter));
            }
            if(newFitness<d_minFitness){
                for(int j=0; j<dimension; ++j){
                    d_bestBat.changeValeur(newSol.valeur(j), j);
                }
                d_minFitness=newFitness;
            }
        }
        cout<<"Iter : "<<iter<<" Meilleur solution : "<<d_minFitness<<endl;
        //printFichier("GRIEWANKFUNCTION.txt", d_minFitness);
        ++iter;
    }
    //affiche_pop();
    //printFichier("BEST_SOLUTION_RASTRIGINFUNCTION.txt", d_minFitness);
}

void myAlgorithm::printFichier(string nomFichier, double fitness)
{
    std::ofstream fName(nomFichier, ios::app);
    if(!fName.is_open()){
        cout<<"Impossible d'ouvrir le fichier"<<endl;
        return;
    }
    fName<<fitness<<'\n';
}

void myAlgorithm::affiche_pop()
{
    cout<<"=================================="<<endl;
    for(int i=0; i<pop_size; ++i){
        cout<<"Bat "<<i<<" 's final ";
        print_solution(d_population[i], d_fitness[i]);
        cout<<endl;
    }
}
