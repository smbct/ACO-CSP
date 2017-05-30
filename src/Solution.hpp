/**
 * \file Solution.hpp
 * \brief definition of a class Solution
 */

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"

/**
 * \class Solution
 * \brief class Solution representing a solution of the Closest String Problem
 */
class Solution {

    public:

        /**
         * \brief constructor
         * \param instance the instance of the CSP problem
         */
        Solution(Instance& instance);

        /**
         * \brief display the solution
         */
        void display();

        /**
         * \brief set the character of the solution in position pos
         * \param pos the position
         * \param character the character
         */
        void setChar(int pos, int character);

        /**
         * \brief return a character at a given position
         * \param pos the position
         * \return the character at position pos
         */
        int getChar(int pos);

        /**
         * \brief return the cost of the solution
         * \return the cost
         */
        int cost();

        /**
         * \brief copy operator
         * \param solution the solution to copy
         */
        Solution& operator=(const Solution& solution);

        /**
         * \brief generate a greedy solution
         */
        void generateGreedy();

        /**
         * \brief generate a random solution
         */
        void generateRandom();


    private: // private methods

        /**
         * \brief recompute all the distances in the matrix and the cost the solution
         */
        void recomputeDistances();


    private: // private attributes

        Instance& _instance; // instance of the CSP problem

        std::vector<int> _solution; // a solution for the problem
        int _cost; // cost of the solution

        std::vector<std::vector<int>> _distances; // matrice of the sub-distances from the solution to the strings of the problem
        int _maxString; // index of the instance string for which the distance is maximum

        bool _updateCost; // indicates if the cost must be recomputed


};

#endif
