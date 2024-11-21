#include "system.h"
#include "random.h"
#include "constants.h"
#include "graph_info.h"
#include <iostream>
#include <vector>

System::System(Graph_info *info) : _g(info) // pass info to graph
{
    _info = info;
    set_info(info);
}

void System::set_info(Graph_info *info)
{
    _info = info;
    _g.update(info); // call update in graph
}

void System::Step(int command, Graph_info *info)
{
    _g.update(info);
}

// draw graph here

void System::Draw(sf::RenderWindow &window)
{

    _g.Draw(window);
}
