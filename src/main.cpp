#include <iostream>
#include <cstdlib>

#include "Instance.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    srand(13245);

    Instance inst;
    inst.load("instances/4-20-10000-2-3.csp");

    // inst.display();

    return 0;
}
