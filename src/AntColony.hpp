/**
 * \file AntColony.hpp
 * \brief definition of the virtual class AntColony
 */

#ifndef ANT_COLONY_HPP
#define ANT_COLONY_HPP

#include "Solution.hpp"
#include <vector>

/**
 * \class AntColony
 * \brief base class for ant colony metaheuristics for the Closest String Problem
 */
class AntColony {

    public:

        /**
         * \brief constructor
         * \param instance instance of the CSP problem
         */
        AntColony(Instance& instance);

        /**
         * \brief solve the CSP problem
         * \param best the best solution found
         */
        void solve(Solution& best);

    protected: // protected methods

        /**
         * \brief build a new solution based on the pheromones and the heuristic information
         * \param solution the solution built
         */
        void buildSolution(Solution& solution);

        /**
         * \brief update the pheromones
         */
        virtual void updatePheromones() = 0;

        /**
         * \brief compute the probabilites for each decision of the artifical ants
         */
        void computeProbas();

        /**
         * \brief make a random choice based on _probas for a character in a given position
         * \param pos the position to make a choice in
         * \return the choice made (character)
         */
        int randomChoice(int pos);

    protected: // protected attributes

        Instance& _instance;
        std::vector<std::vector<double> > _pheromones;
        std::vector<std::vector<double> > _probas;

        double _alpha; // strength of the pheromone information
        double _beta; // strength of the heuristic information
        double _rho; // strength of the pheromones evaporation
};


#endif
