#include <iostream>

#include "Instance.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    Instance inst;
    inst.load("instances/2-30-10000-1-9.csp");

    inst.display();

    return 0;
}
