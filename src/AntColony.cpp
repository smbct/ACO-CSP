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
_instance(instance), _pheromones(instance.stringLength(), vector<double>(instance.nChar(), 0.)),
_probas(instance.stringLength(), vector<double>(instance.nChar(), 0.)),
_nAnts(10), _population(_nAnts, instance)
{

    _alpha = 1.207;
    _beta = 4.67;

    _rho = 0.08;

    _nItMax = 1000;

}

/*----------------------------------------------------------------------------*/
void AntColony::initPheromones() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        for(int j = 0; j < _instance.nChar(); j++) {
            _pheromones.at(i).at(j) = 100.;
        }
    }

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
void AntColony::displayProbas() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        cout << i << " : ";
        for(int j = 0; j < _instance.nChar(); j++) {
            cout << _instance.getIndexChar(j) << " (" << _probas.at(i).at(j) << ") ";
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

        double sum = 0.;

        for(int j = 0; j < _instance.nChar(); j++) {

            // probability: pheroemoneTrail^{\alpha} + heuristicInfo^{\beta}
            _probas.at(i).at(j) = pow(_pheromones.at(i).at(j), _alpha) + pow(_instance.greedyScore(i, j), _beta);
            sum += _probas.at(i).at(j);

            // cout << "phero_score: " << pow(_pheromones.at(i).at(j), _alpha) << " heur_score: " << pow(_instance.greedyScore(i, j), _beta) << endl;
        }

        for(int j = 0; j < _instance.nChar(); j++) {
            _probas.at(i).at(j) /= sum;
        }

    }

}

/*----------------------------------------------------------------------------*/
int AntColony::randomChoice(int pos) {

    double rndRes = Utils::randomNumber();
    double sum = 0.;

    int choice = 0;

    bool stop = false;
    while(!stop && choice < _instance.nChar()) {

        sum += _probas.at(pos).at(choice);

        if(sum <= rndRes) {
            choice ++;
        } else {
            stop = true;
        }
    }

    return choice;
}

/*----------------------------------------------------------------------------*/
void AntColony::evaporatePheromone() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        for(int j = 0; j < _instance.nChar(); j++) {
            _pheromones.at(i).at(j) *= (1.-_rho);
        }
    }

}

/*----------------------------------------------------------------------------*/
void AntColony::depositPheromones(Solution& ant) {

    for(int j = 0; j < _instance.stringLength(); j++) {
        // _pheromones.at(j).at(ant.getChar(j)) += 1./(double)ant.cost();
        _pheromones.at(j).at(ant.getChar(j)) += (1. - (double)ant.cost()/(double)_instance.stringLength());
    }

}

/*----------------------------------------------------------------------------*/
void AntColony::solve(Solution& best) {

    bool init = false;
    int nbIt = 0;

    // probas and pheromone initialisation
    initPheromones();
    computeProbas();

    while(nbIt < _nItMax) {

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
        // evaporation phase
        evaporatePheromone();
        // positive feedback phase from artifical ants
        for(int i = 0; i < _nAnts; i++) {
            depositPheromones(_population.at(i));
        }
        computeProbas();

        // displayProbas();
        // cout << endl << endl;

        nbIt ++;
    }

}
