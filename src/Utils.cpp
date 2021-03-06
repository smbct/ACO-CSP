/**
 * \file Utils.cpp
 * \brief implementation of the functions of the class Utils
 */

#include "Utils.hpp"

#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
double Utils::randomNumber() {

    double number = (double)rand()/(double)(RAND_MAX-1.);

    return number;
}

/*----------------------------------------------------------------------------*/
Utils::Parameters::Parameters() {
    defaultMeta();
    defaultParameters();
}


/*----------------------------------------------------------------------------*/
void Utils::Parameters::extract(int argc, char* argv[]) {

    int i = 1;
    while(i < argc) {

        string str(argv[i]);

        if(str == "--instance") {
            i ++;
            instanceName = argv[i];
        } else if(str == "--algo") {
            i ++;
            string algoName = argv[i];
            if(algoName == "ACO") {
                algorithm = Utils::AntColonyAlgo;
            } else if(algoName == "MaxMin") {
                algorithm = Utils::MaxMin;
            } else if(algoName == "ACS") {
                algorithm = Utils::AntColonySystem;
            }
        } else if(str == "--seed") {
            i ++;
            istringstream stream(argv[i]);
            stream >> seed;
        } else if(str == "--localSearch") {
            localSearch = true;
        } else if(str == "--ants") {
            i ++;
            istringstream stream(argv[i]);
            stream >> nAnts;
        } else if(str == "--iterations") {
            i ++;
            istringstream stream(argv[i]);
            stream >> nIt;
        } else if(str == "--alpha") {
            i ++;
            istringstream stream(argv[i]);
            stream >> alpha;
        } else if(str == "--beta") {
            i ++;
            istringstream stream(argv[i]);
            stream >> beta;
        } else if(str == "--rho") {
            i ++;
            istringstream stream(argv[i]);
            stream >> rho;
        } else if(str == "--a") {
            i ++;
            istringstream stream(argv[i]);
            stream >> a;
        } else if(str == "--convRate") {
            i ++;
            istringstream stream(argv[i]);
            stream >> convRate;
        } else if(str == "--q0") {
            i ++;
            istringstream stream(argv[i]);
            stream >> q0;
        } else if(str == "--initialPheromone") {
            i ++;
            istringstream stream(argv[i]);
            stream >> initPheromone;
        } else if(str == "--default") {
            defaultParameters();
        } else if(str == "--help") {
            displayHelp();
        }

        i ++;
    }

}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::defaultParameters() {

    if(algorithm == Utils::AntColonyAlgo) {
        nAnts = 10;
        alpha = 1.4;
        beta = 2.;
        rho = 0.009;
        nIt = 500;
        initPheromone = 100.;
    } else if(algorithm == Utils::MaxMin) {
        nAnts = 10;
        nIt = 500;
        alpha = 1.8;
        beta = 2.;
        a = 60.;
        initPheromone = 1e20;
        rho = 0.12;
        convRate = 0.16;
    } else if(algorithm == Utils::AntColonySystem) {
        initPheromone = 0.026;
        q0 = 0.6;
        alpha = 1.2;
        beta = 2.5;
        nAnts = 10;
        nIt = 500;
        rho = 0.015;
    }

}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::defaultMeta() {

    instanceName = "?";
    algorithm = AntColonySystem;
    seed = 12345;
    localSearch = false;

}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::display() {
    cout << "Parameters: " << endl;
    cout << "\t- instance: " << instanceName << endl;
    cout << "\t- algorithm: " << (algorithm == AntColonyAlgo ? "ant colony algorithm" : (algorithm == MaxMin ? "max min ant system" : (algorithm  == AntColonySystem ? "ant colony system" : "???") )) << endl;
    cout << "\t- seed: " << seed << endl;
    cout << "\t- local search: " << (localSearch ? "yes" : "no") << endl;
    cout << endl;
    cout << "\t- number of ants: " << nAnts << endl;
    cout << "\t- number of iterations: " << nIt << endl;
    cout << "\t- alpha: " << alpha << endl;
    cout << "\t- beta: " << beta << endl;
    cout << "\t- rho: " << rho << endl;
    if(algorithm == Utils::AntColonySystem || algorithm == Utils::AntColonyAlgo) {
        cout << "\t- pheromones at the begining: " << initPheromone << endl;
    }
    cout << endl;
    if(algorithm == MaxMin) {
        cout << "\t- a (pheromone lower bound): " << a << endl;
        cout << "\t- pheromones are re-initalised if no improvements for " << convRate*100 << "% of the budget" << endl;
    } else if(algorithm == AntColonySystem) {
        cout << "\t- probability of choosing the intensification rule: " << q0 << endl;
    }
}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::displayHelp() {

    cout << "............................Usage................................" << endl;
    cout << "Command line parameters: " << endl << endl << endl;

    cout << "Meta parameters: " << endl;
    cout << "\t--instance <string>          ) name of the instance file" << endl;
    cout << "\t--algorithm <string>         ) name of the algorithm (ACO for ant colony algorithm, MaxMin for max min ant system and ACS for ant colony system)" << endl;
    cout << "\t--seed <int>                 ) value of the random generator seed" << endl;
    cout << "\t--localSearch                ) if specified, a local search is applied to the result " << endl;
    cout << "\t--default                    ) if specified, parameters are initialised to default values (instance name will not be valid)" << endl;
    cout << "\t--help                       ) if specified, this help is shown" << endl;

    cout << endl << endl << "General ant colony parameters: " << endl;
    cout << "\t--ants <int>                 ) number of artifical ants in the colony" << endl;
    cout << "\t--iterations <int>           ) maximum number of iterations allowed" << endl;
    cout << "\t--alpha <float>              ) alpha parameter, strength of the pheromone information" << endl;
    cout << "\t--beta <float>               ) beta parameter, strength of the heuristic information" << endl;
    cout << "\t--rho <float>                ) percentage of the pheromone evaporation (between 0 and 1)" << endl;
    cout << "\t--initialPheromone <float>   ) initial value of the pheromones" << endl;

    cout << endl << endl << "Specific Max Min algorihm parameters: " << endl;
    cout << "\t--a <float>                  ) lower bound of the pheromone = upper bound / a" << endl;
    cout << "\t--convRate <float>           ) percentage of the budget (iterations) before re-initilising the pheromones " << endl;

    cout << endl << endl << "Specific Ant Colony System algorihm parameters: " << endl;
    cout << "\t--q0 <float>                 ) probability of chosing the intensification rule (decision which maximizes phero*heuristic^beta)" << endl;
    cout << endl << endl << endl;
    cout << "Example: ./aco_csp --instance instances/2-30-10000-1-9.csp --algo MaxMin --default --iterations 1 --ants 50" << endl << endl << endl;

}
