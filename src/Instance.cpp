/**
 * \file Instance.cpp
 * \file implementation of the class Instance
 */

#include "Instance.hpp"

#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/*----------------------------------------------------------------------------*/
Instance::Instance() {


}


/*----------------------------------------------------------------------------*/
bool Instance::load(string fileName) {

    ifstream file(fileName);

    if(file) {

        // alphabet size
        file >> _nChar;

        // number of string
        file >> _nString;

        // string length
        file >> _stringLength;
        _indMap.resize(_stringLength);

        // alphabet
        char c;
        for(int i = 0; i < _nChar; i++) {
            file >> c;
            _charInd.insert(pair<char, int>(c, i));
            _indMap.at(i) = c;
        }

        // the strings
        _stringList.resize(_nString, vector<int>(_stringLength, -1));
        string str;
        for(int i = 0; i < _nString; i++) {
            file >> str;
            for(int j = 0; j < _stringLength; j++) {
                _stringList.at(i).at(j) = _charInd.at(str.at(j));
            }
        }

        computeGreedyScore();

        return true;
    } else {
        return false;
    }

}


/*----------------------------------------------------------------------------*/
void Instance::display() {
    cout << "Alphabet: size = " << _nChar << endl;
    for(int i = 0; i < _nChar; i++) {
        cout << _indMap[i] << " ";
    }
    cout << endl << endl << "Number of strings: " << _nString << endl << endl;
    for(int i = 0; i < _nString; i++) {
        for(int j = 0; j < _stringLength; j++) {
            cout << _indMap.at(_stringList.at(i).at(j));
        }
        cout << endl;
    }
}

/*----------------------------------------------------------------------------*/
int Instance::stringLength() {
    return _stringLength;
}

/*----------------------------------------------------------------------------*/
int Instance::nChar() {
    return _nChar;
}

/*----------------------------------------------------------------------------*/
int Instance::nString() {
    return _nString;
}

/*----------------------------------------------------------------------------*/
vector<int>& Instance::getString(int ind) {
    return _stringList.at(ind);
}

/*----------------------------------------------------------------------------*/
char Instance::getIndexChar(int ind) {
    return _indMap.at(ind);
}

/*----------------------------------------------------------------------------*/
void Instance::computeGreedyScore() {

    _greedyScore.resize(_stringLength, vector<double>(_nChar, 0.));

    for(int i = 0; i < _stringLength; i++) {

        // each character wins one point each time it appears in one string
        for(int j = 0; j < _nString; j++) {
            int elt = _stringList.at(j).at(i);
            _greedyScore.at(i).at(elt) += 1.;
        }

        // copute the max to rescale the scores
        double max = 0;

        // the exponential function is applied because the scores were very close to each other
        double scaleFactor = 5.;

        for(int j = 0; j < _nChar; j++) {
            _greedyScore.at(i).at(j) = exp(_greedyScore.at(i).at(j)*scaleFactor);

            if(j == 0 || _greedyScore.at(i).at(j) > max) {
                max = (double)_greedyScore.at(i).at(j);
            }
        }

        for(int j = 0; j < _nChar; j++) {
            _greedyScore.at(i).at(j) = (_greedyScore.at(i).at(j)/max)*1.5;
        }
    }

}

/*----------------------------------------------------------------------------*/
double Instance::greedyScore(int pos, int ch) {
    return _greedyScore.at(pos).at(ch);
}
