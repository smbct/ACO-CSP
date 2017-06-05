/**
 * \file MaxMin.cpp
 * \brief Implementation of the class MaxMin
 */

#include "MaxMin.hpp"

#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
MaxMin::MaxMin(Instance& instance) :
AntColony(instance)
{

    _nItMax = 500;

    _alpha = 1.8;
    _beta = 2.;

    _nAnts = 10;

    _a = 60.;
    _maxPheromone = 1e20;
    _minPheromone = _maxPheromone/_a;
    _rho = 0.12;
    _nItConverge = (int)((double)_nItMax*0.16);

    _population.resize(_nAnts, instance);
}

MaxMin::MaxMin(Instance& instance, Utils::Parameters& parameters):
AntColony(instance, parameters)
{
    _a = parameters.a;
    _nItConverge = (int)((double)_nItMax*parameters.convRate);
    _maxPheromone = 1e20;
    _minPheromone = _maxPheromone/_a;
}


/*----------------------------------------------------------------------------*/
void MaxMin::initPheromones() {

    // initialisation to +infinite
    for(int i = 0; i < _instance.stringLength(); i++) {
        for(int j = 0; j < _instance.nChar(); j++) {
            _pheromones.at(i).at(j) = _maxPheromone;
        }
    }
}

/*----------------------------------------------------------------------------*/
void MaxMin::depositPheromones(Solution& ant) {

    for(int j = 0; j < _instance.stringLength(); j++) {
        _pheromones.at(j).at(ant.getChar(j)) += 1. - (double)ant.cost()/(double)_instance.stringLength();

        // check pheromones bounds
        if(_pheromones.at(j).at(ant.getChar(j)) > _maxPheromone) {
            _pheromones.at(j).at(ant.getChar(j)) = _maxPheromone;
        }
        if(_pheromones.at(j).at(ant.getChar(j)) < _minPheromone) {
            _pheromones.at(j).at(ant.getChar(j)) = _minPheromone;
        }

    }

}

/*----------------------------------------------------------------------------*/
void MaxMin::updateBounds(Solution& best) {

    _maxPheromone = 1.- (_rho* ((double)best.cost()/_instance.stringLength()));
    _minPheromone = _maxPheromone/_a;

}

/*----------------------------------------------------------------------------*/
void MaxMin::checkBounds() {

    for(int i = 0; i < _instance.stringLength(); i++) {

        for(int j = 0; j < _instance.nChar(); j++) {

            // check pheromones bounds
            if(_pheromones.at(i).at(j) > _maxPheromone) {
                _pheromones.at(i).at(j) = _maxPheromone;
            }
            if(_pheromones.at(i).at(j) < _minPheromone) {
                _pheromones.at(i).at(j) = _minPheromone;
            }

        }

    }

}

/*----------------------------------------------------------------------------*/
void MaxMin::solve(Solution& best) {

    bool init = false;
    int nIt = 0;
    int nItRem = _nItConverge; // number of iteration befor pheromone re-init

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
                updateBounds(best);

                // the algorithm has not converged yet
                nItRem = _nItConverge;
            }

            // update bestIt ant
            if(ant == 0 || bestIt->cost() > _population.at(ant).cost()) {
                bestIt = &_population.at(ant);
            }

        }

        if(nItRem <= 0) {
            nItRem = _nItConverge;
            initPheromones();
        } else {
            // update pheromones and probabilities
            evaporatePheromone();
            // only the best want deposits pheromones
            depositPheromones(*bestIt);
            // pheromones bounds
            checkBounds();
        }

        computeProbas();

        nIt ++;
        nItRem --;
    }

}
