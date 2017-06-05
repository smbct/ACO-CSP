/**
 * \file ACS.cpp
 * \brief implementation of the class ACS (Ant Colony System)
 */

#include "ACS.hpp"

#include "Utils.hpp"

#include <iostream>
#include <cmath>

using namespace std;

/*----------------------------------------------------------------------------*/
ACS::ACS(Instance& instance) :
AntColony(instance)
{

    _initPheromone = 0.026;
    _q0 = 0.6;

    _alpha = 1.2;
    _beta = 2.5;

    _nAnts = 10;
    _nItMax = 500;

    _rho = 0.015;

    _population.resize(_nAnts, instance);

    _bestExpl.resize(_instance.stringLength());

}

/*----------------------------------------------------------------------------*/
ACS::ACS(Instance& instance, Utils::Parameters& parameters) :
AntColony(instance, parameters), _bestExpl(_instance.stringLength())
{
    _q0 = parameters.q0;
}

/*----------------------------------------------------------------------------*/
void ACS::depositPheromones(Solution& ant) {

    for(int j = 0; j < _instance.stringLength(); j++) {
        _pheromones.at(j).at(ant.getChar(j)) += _rho*(1. - (double)ant.cost()/(double)_instance.stringLength());
    }

}

/*----------------------------------------------------------------------------*/
void ACS::buildSolution(Solution& solution) {

    // make a choice for each character of the solution
    for(int i = 0; i < _instance.stringLength(); i++) {

        double choice = Utils::randomNumber();
        int character;

        // exploitation rule
        if(choice <= _q0) {
            character = exploitationChoice(i);
        } else { // initial rule
            character = randomChoice(i);
        }

        solution.setChar(i, character);

        // local update rule
        _pheromones.at(i).at(character) = (1.-_rho)*_pheromones.at(i).at(character) + _rho*_initPheromone;

    }
}

/*----------------------------------------------------------------------------*/
int ACS::exploitationChoice(int pos) {
    return _bestExpl.at(pos);
}

/*----------------------------------------------------------------------------*/
void ACS::computeProbas() {

    AntColony::computeProbas();

    // compute the exploitation choice
    for(int i = 0; i < _instance.stringLength(); i++) {
        double max = -1;
        for(int j = 0; j < _instance.nChar(); j++) {
            double score =_pheromones.at(i).at(j)*pow(_instance.greedyScore(i, j), _beta);
            if(j == 0 || score > max) {
                max = score;
                _bestExpl.at(i) = j;
            }
        }
    }

}

/*----------------------------------------------------------------------------*/
void ACS::solve(Solution& best) {

    bool init = false;
    int nIt = 0;

    // probas and pheromones initialisation
    initPheromones();
    computeProbas();

    Solution* bestIt = nullptr;

    while(nIt < _nItMax) {

        // build the population
        for(int ant = 0; ant < _nAnts; ant ++) {

            buildSolution(_population.at(ant));

            // the update best solution
            if(!init || _population.at(ant).cost() < best.cost()) {
                best = _population.at(ant);
                init = true;
                cout << "improvement: " << best.cost() << endl;
            }

            // update bestIt ant
            if(ant == 0 || bestIt->cost() > _population.at(ant).cost()) {
                bestIt = &_population.at(ant);
            }

        }


        // update pheromones and probabilities
        evaporatePheromone();

        // only the best ant deposits pheromones
        depositPheromones(best);

        computeProbas();

        nIt ++;
    }

}
