#include <iostream>
#include <vector>
#include "myAlgorithm.h"
#include "solution.h"
#include "typeFonction.h"
#include <random>
#include <ctime>

int menu()
{
    //SAISIE DES PARAMETRES
    /*int pop, dim, nbExec;
    double bMin, bMax, fMin, fMax;
    cout<<"Population : "; cin>>pop;
    cout<<"Dimension : "; cin>>dim;
    cout<<"Nombre execution : "; cin>>nbExec;
    cout<<"Borne min : "; cin>>bMin;
    cout<<"Borne max : "; cin>>bMax;
    cout<<"Frequence min : "; cin>>fMin;
    cout<<"Frequence max : "; cin>>fMax;*/
    //
    int choix=0;
    cout<<"+-----------------------------+"<<endl;
    cout<<"+ Choix de fontion Benchmark  +"<<endl;
    cout<<"+-----------------------------+"<<endl;
    cout<<"+ 1 -        Sphere           +"<<endl;
    cout<<"+ 2 -      Rastrigin          +"<<endl;
    cout<<"+ 3 -      Rosenbrock         +"<<endl;
    cout<<"+ 4 -      Griewank           +"<<endl;
    cout<<"+ 5 -      Quitter            +"<<endl;
    cout<<"+-----------------------------+"<<endl;
    return choix;
}

void testGriewankFunction()
{

    cout<<"L'ALGO DE BAT"<<endl;
    vector<double> lower(30, -100);
    vector<double> upper(30, 100);
    myAlgorithm algo{30, 30, 66000, lower, upper, 0.0, 5.0, 0, 3.0, 0.0, 1.0, GRIEWANKFUNCTION};
    algo.BAT();
}

void testSphereFunction()
{

    cout<<"L'ALGO DE BAT"<<endl;
    vector<double> lower(30, -100);
    vector<double> upper(30, 100);
    myAlgorithm algo{30, 30, 66667, lower, upper, 0.0, 5.0, 0, 3.0, 0.0, 1.0, SPHEREFUNCTION};
    algo.BAT();
}

void testRastriginFunction()
{

    cout<<"L'ALGO DE BAT"<<endl;
    vector<double> lower(30, -100);
    vector<double> upper(30, 100);
    myAlgorithm algo{30, 30, 66000, lower, upper, 0.0, 5.0, 0, 3.0, 0.0, 1.0, RASTRIGINFUNCTION};
    algo.BAT();
}

void testResenbrockFunction()
{

    cout<<"L'ALGO DE BAT"<<endl;
    vector<double> lower(30, -100);
    vector<double> upper(30, 100);
    myAlgorithm algo{30, 30, 66667, lower, upper, 0.0, 5.0, 0, 3.0, 0.0, 1.0, ROSENBROCKFUNCTION};
    algo.BAT();
}


int main()
{
    srand((unsigned)time(NULL));
    //testGriewankFunction();
    //testSphereFunction();
    //testRastriginFunction();
    testResenbrockFunction();

    return 0;
}

