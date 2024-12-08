#include "plot.h"

Plot::Plot(Graph_info *info)
{
    _info = info;
    set_info(info);
}

void Plot::set_info(Graph_info *info)
{
    _info = info;
    points.clear(); // reset

    string equation = _info->get_equation();

    Tokenizer tokenizer;

    Queue<Token *> infix = tokenizer.tokenize(equation); // tokenize equation

    ShuntingYard sy(infix);
    _post_fix = sy.postfix();

    points = operator()();
}
vector<sf::Vector2f> Plot::operator()()
{
    RPN rpn;

    sf::Vector2f domain = _info->get_domain();
    int num_points = _info->get_points() * 800;
    double increment = (domain.y - domain.x) / num_points;

    CoordTranslator translator(_info);

    vector<sf::Vector2f> graph_points;

    sf::Vector2f origin = _info->get_origin();

    for (double x = domain.x; x <= domain.y; x += increment)
    {

        rpn.set_input(_post_fix);
        double y = rpn(x);

        sf::Vector2f screen_point = translator.translate(sf::Vector2f(x, y));

        graph_points.push_back(screen_point);
    }

    return graph_points;
}