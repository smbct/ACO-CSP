#include <iostream>
#include <cstdlib>

#include "Instance.hpp"
#include "AntColony.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    srand(12345);
    // srand(1);


    Instance inst;
    // inst.load("instances/2-30-10000-1-9.csp");
    inst.load("instances/4-20-10000-1-2.csp");
    // inst.load("src/toy.csp");

    AntColony colony(inst);
    // colony.displayPheromones();

    Solution sol(inst);

    colony.solve(sol);

    // sol.display();
    cout << "best: " << sol.cost() << endl;

    // int opt = 4278;
    int opt = 6312;
    double rpd = (((double)sol.cost() - (double)opt)/(double)opt)*100.;

    cout << "rpd: " << rpd << endl;

    sol.generateRandom();
    cout << "random sol: " << sol.cost() << endl;

    sol.generateGreedy();
    cout << "greedy sol: " << sol.cost() << endl;


    // colony.displayPheromones();

    return 0;
}
