#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <vector>

class solution{
public:
    solution();
    double valeur(int i) const;
    void ajoutValeur(double val);
    void changeValeur(double valeur, int i);
    void printSolution() const;
    double sphereFunction() const;
    double rastriginFunction() const;
    double rosenbrockFunction() const;
    double griewankFunction() const;
    double fonctionFitness(int num_fonc);
private:
    std::vector<double> d_bat;
};

#endif // SOLUTION_H_INCLUDED
