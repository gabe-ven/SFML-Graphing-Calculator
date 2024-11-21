#include "plot.h"

Plot::Plot(Graph_info *info)
{
    set_info();
}
void Plot::set_info()
{
    // equation -> Tokenizer -> infix_Q -> shunting_yard -> _postfix tokenizer and shunting_yard objects are local
    // calls on the parenthesis operator to get a set of screen coords
}
vector<sf::Vector2f> Plot::operator()()
{
    // calls shunting_yard, RPN, coord_transl. objects

    vector<sf::Vector2f> points;

    points.push_back(sf::Vector2f(10, 780));
    points.push_back(sf::Vector2f(550, 400));
    points.push_back(sf::Vector2f(1110, 10));

    return points;
}