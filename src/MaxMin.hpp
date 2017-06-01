/**
 * \file MaxMin.hpp
 * \brief definition of a class MaxMin
 */

#ifndef MAX_MIN_HPP
#define MAX_MIN_HPP

#include "AntColony.hpp"

/**
 * \class MaxMin
 * \brief class MaxMin: Max Min ant colony optimization metaheuristic for the Closes String Problem
 */
class MaxMin : public AntColony {

    public:

        /**
         * \brief costructor
         * \param instance instance of the Closest String Problem
         */
        MaxMin(Instance& instance);

        /**
         * \brief solve the CSP problem
         * \param best the best solution found
         */
        void solve(Solution& best);

    protected: // protected methods

        /**
         * \brief init the pheromone matrix
         */
        virtual void initPheromones();

        /**
         * \brief deposit pheromones
         * \param ant the ant which deposits the pheromones
         */
        virtual void depositPheromones(Solution& ant);

        /**
         * \brief update pheromone bounds
         * \parap bestAnt the best solution so far
         */
        virtual void updateBounds(Solution& best);

    private: // private attributes

        double _maxPheromone;
        double _minPheromone;
        double _a; // determines _minPheromone

        int _nItConverge; // number of iteration to decide if the algorithm converges


};

#endif
