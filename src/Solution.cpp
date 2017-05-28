/**
 * \file Solution.cpp
 * \brief Implementation of the class Solution
 */

#include "Solution.hpp"

#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
Solution::Solution(Instance& instance) :
_instance(instance) {

    _solution.resize(instance.stringLength(), -1);
    _cost = -1;

    _distances.resize(instance.nString(), vector<int>(instance.stringLength(), -1));
    _maxString = -1;

}

/*----------------------------------------------------------------------------*/
void Solution::recomputeDistances() {

    _cost = -1;

    for(unsigned int i = 0; i < _distances.size(); i++) {

        vector<int>& comp = _instance.getString(i);

        for(unsigned int j = 0; j < _distances.at(i).size(); j++) {

            int sum = 0;
            if(j > 0) {
                sum = _distances.at(i).at(j-1);
            }
            _distances.at(i).at(j) = sum + (comp.at(j) == _solution.at(j) ? 0 : 1);

        }

        // update the biggest distance
        if(_distances.at(i).back() > _cost) {
            _cost = _distances.at(i).back();
            _maxString = i;
        }


    }

}

/*----------------------------------------------------------------------------*/
void Solution::display() {

    cout << "Solution: " << endl;
    for(unsigned int i = 0; i < _solution.size(); i++) {
        cout << _solution.at(i);
    }
    cout << endl << "cost: " << _cost << endl;

}

/*----------------------------------------------------------------------------*/
void Solution::setChar(int pos, int character) {
    _solution.at(pos) = character;
}
