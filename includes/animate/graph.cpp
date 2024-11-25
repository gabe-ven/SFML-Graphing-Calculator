#include "graph.h"

Graph::Graph(Graph_info *info) : _plotter(info) // pass info to plotter to fill up the _points vector
{
    _info = info;
    set_info(); // fill up points vector
}

void Graph::set_info()
{
    _points = _plotter();
}

void Graph::update(Graph_info *info)
{
    _info = info;
    _plotter.set_info(info);
    _points = _plotter();
}

void Graph::Draw(sf::RenderWindow &window)
{
    // create x-axis
    sf::RectangleShape x_axis(sf::Vector2f(1200, 1));
    x_axis.setPosition(0, 400);
    x_axis.setFillColor(sf::Color(229, 229, 229));
    window.draw(x_axis);

    // create y-axis
    sf::RectangleShape y_axis(sf::Vector2f(1, 800));
    y_axis.setPosition(550, 0);
    y_axis.setFillColor(sf::Color(229, 229, 229));
    window.draw(y_axis);

    // draw each point onto graph
    for (int i = 0; i < _points.size(); i++)
    {
        sf::CircleShape point(1);
        point.setPosition(_points[i].x - 5, _points[i].y - 5);
        point.setFillColor(sf::Color::Green);
        window.draw(point);
    }
}
