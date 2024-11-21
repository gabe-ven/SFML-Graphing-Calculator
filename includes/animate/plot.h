#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include "graph_info.h"
#include "../../includes/shunting_yard/shunting_yard.h"

#include <SFML/Graphics.hpp>

using namespace std;
class Plot
{
public:
    Plot(Graph_info *info);
    void set_info();
    vector<sf::Vector2f> operator()();

private:
    Queue<Token *> _post_fix;
    Graph_info *_info;
    vector<sf::Vector2f> points;
};

#endif
