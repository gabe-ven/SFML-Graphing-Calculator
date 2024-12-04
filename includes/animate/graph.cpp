#include "graph.h"

Graph::Graph(Graph_info *info) : _plotter(info) // pass info to plotter to fill up the _points vector
{
    _info = info;
    set_info(); // fill up points vector
}

void Graph::set_info()
{
    _points = _plotter(); // pass points to plotter
}

void Graph::update(Graph_info *info)
{
    _info = info;
    _plotter.set_info(info); // pass new info into plot object
    set_info();
}

void Graph::create_axes(sf::RenderWindow &window)
{
    sf::Vector2f origin = _info->get_origin();
    sf::Vector2f window_dimensions = _info->get_window_dimensions();

    // create x-axis
    sf::RectangleShape x_axis(sf::Vector2f(window_dimensions.x, 1));
    x_axis.setPosition(0, origin.y);
    x_axis.setFillColor(sf::Color(229, 229, 229));
    window.draw(x_axis);

    // create y-axis
    sf::RectangleShape y_axis(sf::Vector2f(1, window_dimensions.y));
    y_axis.setPosition(origin.x, 0);
    y_axis.setFillColor(sf::Color(229, 229, 229));
    window.draw(y_axis);
}

void Graph::Draw(sf::RenderWindow &window)
{

    create_axes(window);

    // draw each point onto graph
    for (int i = 0; i < _points.size(); i++)
    {
        sf::CircleShape point(1.5);
        point.setPosition(_points[i].x, _points[i].y);
        point.setFillColor(sf::Color::Green);
        window.draw(point);
    }
}
