#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "graph_info.h"
#include "plot.h"
#include "coord_translator.h"
#include <SFML/Graphics.hpp>

using namespace std;
class Graph
{
public:
    Graph(Graph_info *info);
    void set_info();
    void update(Graph_info *info);
    void create_axes(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window); // draw x & y axis and the points on screen

private:
    Graph_info *_info;
    Plot _plotter;
    vector<sf::Vector2f> _points;
};

#endif
