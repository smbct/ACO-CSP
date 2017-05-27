/**
 * \file MaxMin.hpp
 * \brief definition of a class MaxMin
 */

#ifndef MAX_MIN_HPP
#define MAX_MIN_HPP

#include "Solution.hpp"
#include <vector>

/**
 * \class MaxMin
 * \brief class MaxMin: Max Min ant colony optimization metaheuristic for the Closes String Problem
 */
class MaxMin {

    public:

        /**
         * \brief costructor
         * \param instance instance of the Closest String Problem
         */
        MaxMin(Instance& instance);

        /*
         * \brief solve the CSP problem
         * \param best the best solution found
         */
        void solve(Solution& best);

    private:
        Instance& _instance; // instance of the problem
        std::vector<double> _pheromones;
};

#endif
