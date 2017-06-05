/**
 * \file Utils.cpp
 * \brief implementation of the functions of the class Utils
 */

#include "Utils.hpp"

#include <cstdlib>
#include <sstream>

using namespace std;

/*----------------------------------------------------------------------------*/
double Utils::randomNumber() {

    double number = (double)rand()/(double)(RAND_MAX-1.);

    return number;
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
        }

        i ++;
    }

}

/*----------------------------------------------------------------------------*/
void Utils::Parameters::displayParameters() {


}
