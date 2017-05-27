/**
 * \file Instance.cpp
 * \file implementation of the class Instance
 */

#include "Instance.hpp"

#include <fstream>
#include <iostream>

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
        _invMap.resize(_stringLength);

        // alphabet
        char c;
        for(int i = 0; i < _nChar; i++) {
            file >> c;
            _charInd.insert(pair<char, int>(c, i));
            _invMap.at(i) = c;
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

        _heuristicScore.resize(_stringLength, vector<int>(_nChar, 0));

        return true;
    } else {
        return false;
    }

}


/*----------------------------------------------------------------------------*/
void Instance::display() {
    cout << "Alphabet: size = " << _nChar << endl;
    for(int i = 0; i < _nChar; i++) {
        cout << _invMap[i] << " ";
    }
    cout << endl << endl << "Number of strings: " << _nString << endl << endl;
    for(int i = 0; i < _nString; i++) {
        for(int j = 0; j < _stringLength; j++) {
            cout << _invMap.at(_stringList.at(i).at(j));
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
