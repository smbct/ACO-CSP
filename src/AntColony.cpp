/**
 * \file AntColony.cpp
 * \brief implementation of the class AntColony
 */

#include "AntColony.hpp"

#include "Utils.hpp"

#include <iostream>
#include <cmath>

using namespace std;

/*----------------------------------------------------------------------------*/
AntColony::AntColony(Instance& instance) :
_instance(instance), _pheromones(instance.stringLength(), vector<double>(instance.nChar(), 1000.)),
_probas(instance.stringLength(), vector<double>(instance.nChar(), 0.)),
_nAnts(10), _population(_nAnts, instance)
{

    _alpha = 0.;
    _beta = 2.;

    _rho = 0.3;

}

/*----------------------------------------------------------------------------*/
void AntColony::displayPheromones() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        cout << i << " : ";
        for(int j = 0; j < _instance.nChar(); j++) {
            cout << _instance.getIndexChar(j) << " (" << _pheromones.at(i).at(j) << ") ";
        }
        cout << endl;
    }

}

/*----------------------------------------------------------------------------*/
void AntColony::buildSolution(Solution& solution) {

    // make a choice for each character of the solution
    for(int i = 0; i < _instance.stringLength(); i++) {
        // the solution is modified
        int character = randomChoice(i);
        solution.setChar(i, character);
    }

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

    // cout << endl << endl << "roulette: " << endl;
    // for(int i = 0; i < _instance.nChar(); i++) {
    //     cout << i << ": " << _probas.at(pos).at(i) << " ";
    // }
    // cout << endl << "random number: " << rndRes << endl;
    // cout << "choice: " << choice << endl;


    return choice;
}

/*----------------------------------------------------------------------------*/
void AntColony::updatePheromones() {

    // evaporation phase
    for(int i = 0; i < _instance.stringLength(); i++) {
        for(int j = 0; j < _instance.nChar(); j++) {
            _pheromones.at(i).at(j) *= (1.-_rho);
        }
    }

    // positive feedback phase from artifical ants
    for(int i = 0; i < _nAnts; i++) {
        for(int j = 0; j < _instance.stringLength(); j++) {
            _pheromones.at(j).at(_population.at(i).getChar(j)) += 1./(double)_population.at(i).cost();
        }
    }

}

/*----------------------------------------------------------------------------*/
void AntColony::solve(Solution& best) {

    bool init = false;
    int nbIt = 0;

    // probas initialisation
    computeProbas();

    while(nbIt < 500) {

        // build the population
        for(int ant = 0; ant < _nAnts; ant ++) {
            buildSolution(_population.at(ant));

            // the update best solution
            if(!init || _population.at(ant).cost() < best.cost()) {
                best = _population.at(ant);
                init = true;
                cout << "improvement: " << best.cost() << endl;
            }

        }

        // update pheromones and probabilities
        updatePheromones();
        computeProbas();

        nbIt ++;
    }

}
