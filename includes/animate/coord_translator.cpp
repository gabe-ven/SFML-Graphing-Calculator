#include "coord_translator.h"

CoordTranslator::CoordTranslator(Graph_info *info)
{
    _info = info;
}

sf::Vector2f CoordTranslator::translate(sf::Vector2f point)
{
    sf::Vector2f domain = _info->get_domain();
    sf::Vector2f origin = _info->get_origin();
    sf::Vector2f window_dimensions = _info->get_window_dimensions();

    double scale_x = window_dimensions.x / (domain.y - domain.x); // scale based on range of domain
    double scale_y = window_dimensions.y / (domain.y - domain.x);

    double screen_x, screen_y;

    if (_info->get_polar()) // toggle polar
    {
        double r = point.x;
        double theta = point.y;

        double cart_x = r * cos(theta);
        double cart_y = r * sin(theta);

        screen_x = (cart_x - domain.x) * scale_x;
        screen_y = window_dimensions.y / 2 - (cart_y * scale_y);
    }
    else
    {
        screen_x = (point.x - domain.x) * scale_x;
        screen_y = window_dimensions.y / 2 - (point.y * scale_y);
    }

    return sf::Vector2f(screen_x, screen_y);
}

sf::Vector2f CoordTranslator::operator()(sf::Vector2f point)
{
    return translate(point);
}
