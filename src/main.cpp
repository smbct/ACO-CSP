#include <iostream>
#include <cstdlib>

#include "Instance.hpp"
#include "AntColony.hpp"
#include "MaxMin.hpp"
#include "ACS.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    srand(12345);
    // srand(1);


    Instance inst;
    inst.load("instances/2-30-10000-1-9.csp");
    // inst.load("instances/4-20-10000-1-2.csp");
    // inst.load("instances/20-50-10000-1-1.csp");
    // inst.load("src/toy.csp");

    // AntColony colony(inst);
    // MaxMin colony(inst);
    ACS colony(inst);
    // colony.displayPheromones();

    Solution sol(inst);

    colony.solve(sol);
    // colony.displayPheromones();

    // sol.display();


    cout << "best: " << sol.cost() << endl;
    sol.localSearch();
    cout << "best + local search: " << sol.cost() << endl;


    int opt = 4278;
    // int opt = 6312;
    // int opt = 8835;
    double rpd = (((double)sol.cost() - (double)opt)/(double)opt)*100.;

    cout << "rpd: " << rpd << endl;

    sol.generateRandom();
    cout << "random sol: " << sol.cost() << endl;
    sol.localSearch();
    cout << "generate random + local search: " << sol.cost() << endl;

    sol.generateGreedy();
    cout << "greedy sol: " << sol.cost() << endl;

    sol.localSearch();
    cout << "greedy sol + local search: " << sol.cost() << endl;


    // sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "test");
    //
    // while(window.isOpen()) {
    //
    //     sf::Event event;
    //
    //     while(window.pollEvent(event)) {
    //
    //         if(event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //
    //         window.display();
    //     }
    // }

    return 0;
}
