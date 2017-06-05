/**
 * \file Utils.hpp
 * \brief utilities for the artificial ant framework
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

/**
 * \class Utils
 * \brief definition of the class Utils containing the utilites functions
 */
class Utils {

    public: // public enum

        enum algo{
            AntColonyAlgo,
            MaxMin,
            AntColonySystem,
            None
        };

    public: // public class

        /**
         * \class Parameters
         * \brief parameters of the program
         */
        class Parameters {

            public:

                /**
                 * \brief default construcor, default initialisation
                 */
                Parameters();

                /**
                 * \brief extract the parameters from the command line arguments
                 * \param argc number of parameters
                 * \param argv the strings containing the parameters
                 */
                void extract(int argc, char* argv[]);

                /**
                 * \brief display the parameters chosen
                 */
                void display();

                /**
                 * \brief display the help
                 */
                void displayHelp();

                /**
                 * \brief default parameters for ant algorithm chosen (best found)
                 */
                void defaultParameters();

                /**
                 * \brief default parameters for the meta parameters
                 */
                void defaultMeta();

                // meta parameters
                std::string instanceName; // name of the instance file
                Utils::algo algorithm; // the algorithm chosen
                int seed; // the seed used for the random generator
                bool localSearch; // true iff a local searh is performed

                // general ant colony parameters
                int nAnts; // number of ants
                int nIt; // maximum number of iteration allowed
                double alpha; // strength of the pheromone information
                double beta; // strength of the heuristic information
                double rho; // pheromones evaporation
                double initPheromone; // amount of pheromone at the begining

                // maxmin specific parameters
                double a; // control the level of the pheromone bound
                double convRate; // percentage of iteration allowed before pheromone re-initialisation

                // ant colony system specific parameters
                double q0; // probability of choosing the intensification decision rule
        };

    public: // public static methods

        /**
         * \brief return a random number between 0 and 1 (one excluded)
         * \return the random number
         */
        static double randomNumber();

    private:

        /**
         * \brief constructor, should not be instanciated
         */
        Utils();
};

#endif
