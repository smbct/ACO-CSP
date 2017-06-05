/**
 * \file Instance.hpp
 * \brief declaration of an Instance class
 */

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <string>
#include <vector>
#include <map>

/**
 * \class Instance
 * \brief manage an instance of the csp problem
 */
class Instance {

    public:

        /**
         * \brief default constructor
         */
        Instance();

        /**
         * \brief load a instance of the CSP problem
         * \param fileName the name of the file
         * \return true iff the instance has been opened without troubles
         */
        bool load(std::string fileName);

        /**
         * \brief display the instance
         */
        void display();

        /**
         * \brief return the length of the strings
         * \return the length of the strings
         */
        int stringLength();

        /**
         * \brief number of strings of the problem
         * \return number of strings of the problem
         */
        int nString();

        /**
         * \brief number of characters of the alphabet
         * \return the number of character
         */
        int nChar();

        /**
         * \brief get the character represented by the index index
         * \param ind the index that represents the character in the problem
         * \return the character
         */
        char getIndexChar(int ind);

        /**
         * \brief access a string
         * \param ind the index of the string
         * \return a reference toward a string
         */
        std::vector<int>& getString(int ind);

        /**
         * \brief returns the greedy score of a character for a given position
         * \param pos the position in the strings
         * \param ch the character
         */
        double greedyScore(int pos, int ch);

    private: // private methods

        /**
         * \brief compute a greedy score for each character at each position of the strings
         */
        void computeGreedyScore();

    private: // private attributes

        int _nChar; // number of characters in the alphabet
        std::map<char, int> _charInd; // index of the characters
        std::vector<char> _indMap; // inverse map, find the character from the index

        int _nString; // number of strings
        int _stringLength;
        std::vector<std::vector<int> > _stringList; // list of the strings

        std::vector<std::vector<double>> _greedyScore; // greedy score for each position


};

#endif
