#include "solution.h"
#include "typeFonction.h"
#include <iostream>
#include <cmath>

solution::solution()
    : d_bat{}
{

}

double solution::valeur(int i) const
{
    return d_bat[i];
}

void solution::ajoutValeur(double val)
{
    d_bat.push_back(val);
}

void solution::changeValeur(double valeur, int i)
{
    d_bat[i]=valeur;
}

void solution::printSolution() const
{
    for(unsigned i=0; i<d_bat.size(); ++i){
        std::cout<<d_bat[i]<<" ";
    }
}

double solution::sphereFunction() const
{
    //double f_bias=-450;
    double val{0.0};
    for(unsigned i=0; i<d_bat.size(); ++i){
        val+=d_bat[i]*d_bat[i];
    }
    return val;
}

double solution::rastriginFunction() const
{
    //double f_bias=-330;
    double val{0.0};
    for(unsigned i=0; i<d_bat.size(); ++i){
        double valCos=std::cos((2*M_PI*d_bat[i])/180);
        val+=(d_bat[i]*d_bat[i])-10*valCos+10;
    }
    return val;
}

double solution::rosenbrockFunction() const
{
    //double f_bias=390;
    double val{0.0};
    for(unsigned i=0; i<d_bat.size()-1; ++i){
        double memb1=(pow(d_bat[i], 2.0)-d_bat[i+1]);
        double memb2=(d_bat[i]-1);
        val+=100*pow(memb1, 2.0) + pow(memb2, 2.0);
    }
    return val;
}

double solution::griewankFunction() const
{
    //double f_bias=-180;
    double somme{0.0}, produit{1};
    for(unsigned i=0; i<d_bat.size(); ++i){
        somme+=(d_bat[i]*d_bat[i]);
        produit*=std::cos((d_bat[i] / std::sqrt(static_cast<double>(i + 1)))*M_PI/180);
    }
    return (somme/4000)-produit+1;
}

double solution::fonctionFitness(int num_fonc)
{
    double val{0.0};
    switch(num_fonc)
    {
        case SPHEREFUNCTION     : val=sphereFunction(); break;
        case RASTRIGINFUNCTION  : val=rastriginFunction(); break;
        case ROSENBROCKFUNCTION : val=rosenbrockFunction(); break;
        case GRIEWANKFUNCTION   : val=griewankFunction(); break;
    }
    return val;
}
