#include "coord_translator.h"

CoordTranslator::CoordTranslator(Graph_info *info)
{
    _info = info;
}
sf::Vector2f CoordTranslator::translate(sf::Vector2f point)
{
    sf::Vector2f window_dimensions = _info->get_window_dimensions();
    sf::Vector2f origin = _info->get_origin();
    sf::Vector2f domain = _info->get_domain();

    double scale_x = window_dimensions.x / (domain.y - domain.x); // divide width of domain by width of window
    double scale_y = window_dimensions.y / (domain.y - domain.x); // divide height of domain by height of window

    _info->set_scale(scale_x, scale_y); // set scale to calculated scale

    double screen_x = (point.x * scale_x) + origin.x; // convert x coordinate of graph to screen coords
    double screen_y = origin.y - (point.y * scale_y); // convert y coordinate of graph to screen coords

    return sf::Vector2f(screen_x, screen_y);
}
sf::Vector2f CoordTranslator::operator()(sf::Vector2f point)
{
    return translate(point);
}
