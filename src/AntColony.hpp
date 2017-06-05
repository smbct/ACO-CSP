/**
 * \file AntColony.hpp
 * \brief definition of the virtual class AntColony
 */

#ifndef ANT_COLONY_HPP
#define ANT_COLONY_HPP

#include "Solution.hpp"
#include "Utils.hpp"
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
         * \brief constructor
         * \param parameters the parameters of the algorithm
         */
        AntColony(Instance& instance, Utils::Parameters& parameters);

        /**
         * \brief solve the CSP problem
         * \param best the best solution found
         */
        virtual void solve(Solution& best);

        /**
         * \brief display the pheromone matrix of the algorithm
         */
        virtual void displayPheromones();

        /**
         * \brief display the probabilities matrix of the algorithm
         */
        void displayProbas();

        /**
         * \brief default destructor
         */
        virtual ~AntColony();

    protected: // protected methods

        /**
         * \brief build a new solution based on the pheromones and the heuristic information
         * \param solution the solution built
         */
        virtual void buildSolution(Solution& solution);

        /**
         * \brief compute the probabilites for each decision of the artifical ants
         */
        virtual void computeProbas();

        /**
         * \brief make a random choice based on _probas for a character in a given position
         * \param pos the position to make a choice in
         * \return the choice made (character)
         */
        int randomChoice(int pos);

        /**
         * \brief evaporate the artificial pheromones
         */
        void evaporatePheromone();

        /**
         * \brief deposit pheromones
         * \param ant the ant which deposits the pheromones
         */
        virtual void depositPheromones(Solution& ant);

        /**
         * \brief init the pheromone matrix
         */
        virtual void initPheromones();

    protected: // protected attributes

        Instance& _instance;
        std::vector<std::vector<double> > _pheromones;
        std::vector<std::vector<double> > _probas;

        double _alpha; // strength of the pheromone information
        double _beta; // strength of the heuristic information
        double _rho; // strength of the pheromones evaporation
        int _nAnts; // size of the population
        int _nItMax; // maximum number of iteration
        double _initPheromone; // amount of pheromones at the begining

        std::vector<Solution> _population; // population of artificial ants
};


#endif
