#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <vector>
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace std;
class Graph_info
{
public:
    Graph_info();

    void set_equation(const string &equation);
    void set_points(int points);
    void set_window_dimensions(double width, double height);
    void set_origin(double x, double y);
    void set_scale(double x_scale, double y_scale);
    void set_domain(double x_min, double x_max);
    void set_polar(bool _isPolar);

    string get_equation() const;
    int get_points() const;
    sf::Vector2f get_window_dimensions() const;
    sf::Vector2f get_origin() const;
    sf::Vector2f get_scale() const;
    sf::Vector2f get_domain() const;
    bool get_polar();

private:
    string _equation;
    int _points; // # of points
    double _zoom;
    bool _isPolar;
    sf::Vector2f _window_dimensions;
    sf::Vector2f _origin; // graph's (0,0) in screen coords
    sf::Vector2f _scale;
    sf::Vector2f _domain;
};

#endif
