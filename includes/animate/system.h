#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "graph.h"
#include <SFML/Graphics.hpp>

using namespace std;
class System
{
public:
    System();
    void set_info();
    void Step(int command);              // Calls graph::step()
    void Draw(sf::RenderWindow &window); // Calls graph::draw()

private:
    Graph _g;
};

#endif // SYSTEM_H
