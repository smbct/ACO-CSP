/**
 * \file Utils.cpp
 * \brief utilities for the arificial ant framework
 */

#ifndef UTILS_HPP
#define UTILS_HPP

/**
 * \class Utils
 * \brief definition of the class Utils containing the utilites functions
 */
class Utils {

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
