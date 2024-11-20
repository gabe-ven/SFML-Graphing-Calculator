#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
class Graph_info
{
public:
    Graph_info();

private:
    string _equation;
    int _points; // # of points
    vector<sf::Vector2f> _window_dimensions;
    vector<sf::Vector2f> _origin; // graph's (0,0) in src coords
    vector<sf::Vector2f> _scale;
    vector<sf::Vector2f> _domain;
};

#endif
