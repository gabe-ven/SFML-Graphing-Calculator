#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include "graph_info.h"
#include <SFML/Graphics.hpp>

using namespace std;
class Plot
{
public:
    Plot(Graph_info *info);
    void set_info();
    double operator()();

private:
    Graph_info *_info;
};

#endif
