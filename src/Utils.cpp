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
        } else if(str == "--nAnt") {
            i ++;
            istringstream stream(argv[i]);
            stream >> nAnts;
        } else if(str == "--nIt") {
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
        }

        i ++;
    }

}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::defaultParameters() {

    if(algorithm == Utils::AntColonyAlgo) {
        nAnts = 10;
        alpha = 1.105;
        beta = 4.67;
        rho = 0.078;
        nIt = 1000;
        initPheromone = 1e7;
    } else if(algorithm == Utils::MaxMin) {
        nAnts = 10;
        nIt = 1000;
        alpha = 1.6;
        beta = 2.;
        a = 1000.;
        initPheromone = 1e20;
        rho = 0.4;
        convRate = 0.16;
    } else if(algorithm == Utils::AntColonySystem) {
        initPheromone = 5;
        q0 = 0.7;
        alpha = 2.4;
        beta = 2.;
        nAnts = 10;
        nIt = 1000;
        rho = 0.05;
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

    cout << "Parameters chosen: " << endl;
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
    cout << endl;
    if(algorithm == MaxMin) {
        cout << "\t- a (pheromone lower bound): " << a << endl;
        cout << "\t- pheromones re-initalised after " << convRate*100 << "% of the budget" << endl;
    } else if(algorithm == AntColonySystem) {
        cout << "\t- probability of choosing the intensification rule: " << q0 << endl;
        cout << "\t- pheromones at the begining: " << initPheromone << endl;
    }
}
