/**
 * \file AntColony.cpp
 * \brief implementation of the class AntColony
 */

#include "AntColony.hpp"

#include "Utils.hpp"

#include <cmath>

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

        int character = randomChoice(i);

        // the solution is modified

    }

    // the score of the solution is recomputed

}


/*----------------------------------------------------------------------------*/
void AntColony::computeProbas() {

    for(int i = 0; i < _instance.stringLength(); i++) {

        double sum = 0;

        for(int j = 0; j < _instance.nChar(); j++) {
            // probability: pheroemoneTrail^{\alpha} + heuristicInfo^{\beta}
            _probas.at(i).at(j) = pow(_pheromones.at(i).at(j), _alpha) + pow(_instance.greedyScore(i, j), _beta);
            sum += _probas.at(i).at(j);
        }

        // probas are normalized
        for(int j = 0; j < _instance.nChar(); j++) {
            _probas.at(i).at(j) /= sum;
        }

    }

}

/*----------------------------------------------------------------------------*/
int AntColony::randomChoice(int pos) {

    double rndRes = Utils::randomNumber();
    double sumProbas = 0.;

    int choice = 0;

    bool stop = false;
    while(!stop) {

        sumProbas += _probas.at(pos).at(choice);

        if(sumProbas <= rndRes) {
            choice ++;
        } else {
            stop = true;
        }
    }

    return choice;
}
