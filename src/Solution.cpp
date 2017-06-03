/**
 * \file Solution.cpp
 * \brief Implementation of the class Solution
 */

#include "Solution.hpp"
#include "Utils.hpp"

#include <iostream>
#include <cmath>

using namespace std;

/*----------------------------------------------------------------------------*/
Solution::Solution(Instance& instance) :
_instance(instance), _updateCost(true) {

    _solution.resize(instance.stringLength(), -1);
    _cost = -1;

    _distances.resize(instance.nString(), 0);
    _maxString = -1;

}

/*----------------------------------------------------------------------------*/
void Solution::recomputeDistances() {

    _updateCost = false;

    _cost = -1;

    fill(_distances.begin(), _distances.end(), 0);

    // for all strings of the instance, compute the hamming distance to the solution
    for(unsigned int i = 0; i < _distances.size(); i++) {
        vector<int>& comp = _instance.getString(i);
        for(int j = 0; j < _instance.stringLength(); j++) {
            // if the character is different, the distance is bigger
            if(comp.at(j) != _solution.at(j)) {
                _distances.at(i) ++;
            }
        }

        // update the biggest distance
        if(i == 0 || _distances.at(i) > _cost) {
            _cost = _distances.at(i);
            _maxString = i;
        }

    }

}

/*----------------------------------------------------------------------------*/
void Solution::display() {

    cout << "Solution: " << endl;
    for(unsigned int i = 0; i < _solution.size(); i++) {
        cout << _instance.getIndexChar(_solution.at(i));
    }
    cout << endl << "cost: " << _cost << endl;

}

/*----------------------------------------------------------------------------*/
void Solution::setChar(int pos, int character) {
    _solution.at(pos) = character;
    _updateCost = true;
}

/*----------------------------------------------------------------------------*/
void Solution::setCharUpdate(int pos, int character) {

    for(int i = 0; i < _instance.nString(); i++) {

        // the previous choice is canceled
        if(_instance.getString(i).at(pos) != _solution.at(pos)) {
            _distances.at(i) --;
        }

        if(_instance.getString(i).at(pos) != character) {
            _distances.at(i) ++;
        }

        // the max distance is updated
        if(i == 0 || _distances.at(i) > _cost) {
            _cost = _distances.at(i);
            _maxString = i;
        }

    }

    _solution.at(pos) = character;

}

/*----------------------------------------------------------------------------*/
int Solution::getChar(int pos) {
    return _solution.at(pos);
}

/*----------------------------------------------------------------------------*/
int Solution::cost() {

    if(_updateCost) {
        recomputeDistances();
    }

    return _cost;
}

/*----------------------------------------------------------------------------*/
Solution& Solution::operator=(const Solution& solution) {

    _instance = solution._instance;
    _solution = solution._solution;
    _cost = solution._cost;
    _distances = solution._distances;
    _maxString = solution._maxString;
    _updateCost = solution._updateCost;

    return *this;
}

/*----------------------------------------------------------------------------*/
void Solution::generateGreedy() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        int charMin = -1;
        double scoreMax = -1;
        for(int j = 0; j < _instance.nChar(); j++) {
            if(j == 0 || scoreMax < _instance.greedyScore(i, j)) {
                charMin = j;
                scoreMax = _instance.greedyScore(i, j);
            }
        }
        setChar(i, charMin);
    }

}

/*----------------------------------------------------------------------------*/
void Solution::generateRandom() {

    for(int i = 0; i < _instance.stringLength(); i++) {
        setChar(i, (int)floor(Utils::randomNumber()*_instance.nChar()));
    }

}

/*----------------------------------------------------------------------------*/
void Solution::localSearch() {

    bool stop = false;

    int bestPos = -1;
    int bestChar = -1;
    int bestCost = -1;

    while(!stop) {

        // for all positions, all the porribles characters are tried
        for(int i = 0; i < _instance.stringLength(); i++) {

            int actualChoice = _solution.at(i);

            for(int j = 0; j < _instance.nChar(); j++) {
                if(j != actualChoice) {

                    setCharUpdate(i, j);
                    // if the solution is better, the previously best found is replaced
                    if(bestCost == -1 || cost() < bestCost) {
                        bestCost = cost();
                        bestPos = i;
                        bestChar = j;
                    }

                }
            }
            // the move is canceled
            setCharUpdate(i, actualChoice);

        }

        // if the best move improves the result, it is applied
        if(bestCost < cost()) {
            setCharUpdate(bestPos, bestChar);
        } else { // otherwise, the local search is stopped
            stop = true;
        }

    }

}
