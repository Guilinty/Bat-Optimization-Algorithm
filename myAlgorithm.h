#pragma once
#ifndef _MYALGO_OPT_
#define _MYALGO_OPT_
#include "OptUHA.h"


class myAlgorithm : public OptUHA
{
public:
	// mettre un constructeur avec des paramètres ici
	myAlgorithm(int nbPop, int dim, int nbIter, vector<double> lower, vector<double> upper,
              double fmin, double fmax, double Amin, double Amax, double rMin, double rMax, int func_num);
	void BAT();
protected:
    // déclarer les paramètres de votre algorithme ici
	vector<solution> d_population;
	vector<solution> d_velocity;
	double d_fMin, d_fMax;
	double d_aMin, d_aMax;
	double d_rMin, d_rMax;
	vector<double> d_frequency;
    vector<double> d_pulseRate;
    vector<double> d_loudness;
    solution d_bestBat;
    double d_minFitness;
    int d_func_num;
    static constexpr double ALPHA{0.9};
    static constexpr double GAMMA{0.9};

protected:
	solution FindBestSolution() const;
	int IndexBestSolution() const;
	void evaluate_pop(int funct_num, vector<double>& fitness);
	double evaluate_individual(int funct_num, solution& ind) const;
	vector<solution> velocityPop();
	vector<double> randomValues(double min, double max);
	double meanOfbats(const vector<double> loudness) const;
	void randomSolution(solution& s);
	void printFichier(string nomFichier, double fitness);
	void affiche_pop();



};

#endif
