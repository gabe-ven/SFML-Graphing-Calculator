#ifndef COORD_TRANSLATOR_H
#define COORD_TRANSLATOR_H
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include "graph_info.h"
#include <SFML/Graphics.hpp>

using namespace std;

class CoordTranslator
{
public:
    CoordTranslator(Graph_info *info);
    sf::Vector2f translate(sf::Vector2f point);
    sf::Vector2f operator()(sf::Vector2f point);

private:
    Graph_info *_info;
};

#endif
