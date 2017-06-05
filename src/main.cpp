#include <iostream>
#include <cstdlib>

#include "Instance.hpp"
#include "AntColony.hpp"
#include "MaxMin.hpp"
#include "ACS.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    Utils::Parameters parameters;
    parameters.extract(argc, argv);
    parameters.display();

    srand(parameters.seed);

    Instance instance;
    instance.load(parameters.instanceName);

    AntColony* colony = nullptr;

    // select the chosen algorithm
    if(parameters.algorithm == Utils::AntColonyAlgo) {
        colony = new AntColony(instance, parameters);
    } else if(parameters.algorithm == Utils::MaxMin) {
        colony = new MaxMin(instance, parameters);
    } else if(parameters.algorithm == Utils::AntColonySystem) {
        colony = new ACS(instance, parameters);
    }

    Solution sol(instance);

    colony->solve(sol);
    // colony.displayPheromones();

    // sol.display();


    cout << "best: " << sol.cost() << endl;
    sol.localSearch();
    cout << "best + local search: " << sol.cost() << endl;


    // int opt = 4278;
    // int opt = 6312;
    // int opt = 8835;
    // double rpd = (((double)sol.cost() - (double)opt)/(double)opt)*100.;

    // cout << "rpd: " << rpd << endl;

    sol.generateRandom();
    cout << "random sol: " << sol.cost() << endl;
    sol.localSearch();
    cout << "generate random + local search: " << sol.cost() << endl;

    sol.generateGreedy();
    cout << "greedy sol: " << sol.cost() << endl;

    sol.localSearch();
    cout << "greedy sol + local search: " << sol.cost() << endl;

    delete colony;

    return 0;
}
