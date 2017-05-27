/**
 * \file AntColony.cpp
 * \brief implementation of the class AntColony
 */

#include "AntColony.hpp"

using namespace std;

/*----------------------------------------------------------------------------*/
AntColony::AntColony(Instance& instance) :
_instance(instance), _pheromones(instance.stringLength(), vector<double>(instance.nChar(), 1.0/instance.nChar()))
{


}

/*----------------------------------------------------------------------------*/
void AntColony::buildSolution(Solution& solution) {

    // make a choice for each character of the solution
    for(int i = 0; i < _instance.stringLength(); i++) {



    }

}
