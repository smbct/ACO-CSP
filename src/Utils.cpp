/**
 * \file Utils.cpp
 * \brief implementation of the functions of the class Utils
 */

#include "Utils.hpp"

#include <cstdlib>

/*----------------------------------------------------------------------------*/
double Utils::randomNumber() {

    double number = (double)rand()/(double)(RAND_MAX-1.);

    return number;
}
