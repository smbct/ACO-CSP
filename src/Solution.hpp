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

    // private methods
    private:

        /**
         * \brief recompute all the distances in the matrix
         */
        void recomputeDistances();

    // private attributes
    private:

        Instance& _instance; // instance of the CSP problem

        std::vector<int> _solution; // a solution for the problem
        int _cost; // cost of the solution

        std::vector<std::vector<int>> _distances; // matrice of the sub-distances
        int _maxString; // index of the instance string for which the distance is maximum


};

#endif
