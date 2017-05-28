#include <iostream>
#include <cstdlib>

#include "Instance.hpp"
#include "AntColony.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    srand(13245);

    Instance inst;
    inst.load("instances/2-30-10000-1-9.csp");

    // inst.display();

    AntColony colony(inst);

    Solution sol(inst);

    colony.solve(sol);

    // sol.display();
    cout << "best: " << sol.cost() << endl;

    return 0;
}
