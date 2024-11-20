#include "graph.h"

Graph::Graph()
{
    set_info();
}

void Graph::set_info()
{
    // 3 points
    _points.push_back(sf::Vector2f(10, 780));
    _points.push_back(sf::Vector2f(550, 400));
    _points.push_back(sf::Vector2f(1110, 10));
}

void Graph::Step(int command)
{
    return;
}

void Graph::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape x_axis(sf::Vector2f(1200, 2));
    x_axis.setPosition(0, 400);
    x_axis.setFillColor(sf::Color::White);
    window.draw(x_axis);

    sf::RectangleShape y_axis(sf::Vector2f(2, 800));
    y_axis.setPosition(550, 0);
    y_axis.setFillColor(sf::Color::White);
    window.draw(y_axis);

    for (int i = 0; i < _points.size(); i++)
    {
        sf::CircleShape point(5);
        point.setPosition(_points[i].x - 5, _points[i].y - 5);
        point.setFillColor(sf::Color::Red);
        window.draw(point);
    }
}
