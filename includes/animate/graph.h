#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "graph_info.h"
#include <SFML/Graphics.hpp>

using namespace std;
class Graph
{
public:
    Graph();
    void Step(int command);
    void set_info();
    void Draw(sf::RenderWindow &window); // draw x & y axis and the points on screen

private:
    // Graph_info *_info;
    // Plot _plotter;
    vector<sf::Vector2f> _points;
};

#endif
