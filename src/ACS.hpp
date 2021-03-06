/**
 * \file ACS.hpp
 * \brief definition of the class ACS (Ant Colony System)
 */

#ifndef ACS_HPP
#define ACS_HPP

#include "AntColony.hpp"

/**
 * \class ACS
 * \brief class ACS for the Ant Colony System metaheuristic
 */
class ACS : public AntColony{

    public: // public methods

        /**
         * \brief constructor
         * \param instance instance of the problem
         */
        ACS(Instance& instance);

        /**
         * \brief constructor
         * \param instance instance of the problem
         * \param parameters parameters of the algorithm
         */
        ACS(Instance& instance, Utils::Parameters& parameters);

        /**
         * \brief solve the CSP problem
         * \param best the best solution found
         */
        virtual void solve(Solution& best);

    protected: // protected methods

        /**
         * \brief deposit pheromones
         * \param ant the ant which deposits the pheromones
         */
        virtual void depositPheromones(Solution& ant);

        /**
         * \brief build a new solution based on the pheromones and the heuristic information, and deposit pheromones at the same time (local rule)
         * \param solution the solution built
         */
        virtual void buildSolution(Solution& solution);

        /**
         * \brief return the exploitation choice for this position (the max of pheromone*heuristic_info)
         * \param pos the position to make a choice in
         * \return the choice made (character)
         */
        virtual int exploitationChoice(int pos);

        /**
         * \brief compute the probabilites for each decision of the artifical ants and the exploitation choice too
         */
        virtual void computeProbas();

    private: // private attributes

        double _q0; // probability of exploitation

        std::vector<int> _bestExpl; // best choice for exploitation

};

#endif
