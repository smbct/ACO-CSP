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

    if(argc > 1) {
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

        if(parameters.localSearch) {
            sol.localSearch();
        }
        cout << "best: " << sol.cost() << endl;

        delete colony;
    } else {
        parameters.displayHelp();
    }


    return 0;
}
