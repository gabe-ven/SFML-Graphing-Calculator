#include "graph_info.h"

Graph_info::Graph_info()
{
    set_equation("X^2");
    set_points(11);
    set_window_dimensions(1120, 800);
    set_origin(560, 400);
    set_scale(1, 1);
    set_domain(-5, 5);
}

void Graph_info::set_equation(const string &equation)
{
    _equation = equation;
}

void Graph_info::set_points(int points)
{
    _points = points;
}

void Graph_info::set_window_dimensions(double width, double height)
{
    _window_dimensions = sf::Vector2f(width, height);
}

void Graph_info::set_origin(double x, double y)
{
    _origin = sf::Vector2f(x, y);
}

void Graph_info::set_scale(double x_scale, double y_scale)
{
    _scale = sf::Vector2f(x_scale, y_scale);
}

void Graph_info::set_domain(double x_min, double x_max)
{
    _domain = sf::Vector2f(x_min, x_max);
}

string Graph_info::get_equation() const
{
    return _equation;
}

int Graph_info::get_points() const
{
    return _points;
}

sf::Vector2f Graph_info::get_window_dimensions() const
{
    return _window_dimensions;
}

sf::Vector2f Graph_info::get_origin() const
{
    return _origin;
}

sf::Vector2f Graph_info::get_scale() const
{
    return _scale;
}

sf::Vector2f Graph_info::get_domain() const
{
    return _domain;
}
