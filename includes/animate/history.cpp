#include "history.h"

History::History()
{
    const double HEIGHT = 500.0;

    _left = SCREEN_WIDTH * 4 / 5;
    _width = SIDE_BAR - 2;

    rect.setFillColor(sf::Color(50, 50, 50));

    rect.setPosition(sf::Vector2f(_left, 100));
    rect.setSize(sf::Vector2f(_width, HEIGHT));

    // Load font
    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout << "History CTOR: Font failed to load" << std::endl;
        exit(-1);
    }

    equations.setFont(font);
    equations.setCharacterSize(20);
    equations.setStyle(sf::Text::Bold);
    equations.setFillColor(sf::Color(0, 225, 0));
    equations.setOutlineColor(sf::Color(0, 225, 0));
    equations.setOutlineThickness(0.5);
}

void History::addHistory(const string &equation)
{
    history.push_back(equation);
    if (history.size() > 7)
    {
        history.erase(history.begin());
    }
}

void History::loadEquations()
{
    ifstream file("functions.txt");

    if (!file.is_open())
    {
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            history.push_back(line);
        }
    }

    file.close();

    while (history.size() > 7)
    {
        history.erase(history.begin());
    }
}

void History::draw(sf::RenderWindow &window)
{
    const double VERTICAL_LINE_SPACING = 30.0;
    const double BOTTOM_MARGIN = 5.0;
    const double BOX_HEIGHT = 40.0;

    window.draw(rect);

    float height = 105;

    for (vector<string>::iterator it = history.begin(); it != history.end(); it++)
    {
        if (it->empty())
        {
            continue;
        }

        equations.setString(*it);

        sf::RectangleShape box;
        box.setSize(sf::Vector2f(_width - 30, BOX_HEIGHT));
        box.setPosition(_left + 15, height);
        box.setFillColor(sf::Color(44, 44, 44));
        box.setOutlineColor(sf::Color(0, 225, 0));
        box.setOutlineThickness(2);

        window.draw(box);

        equationBoxes.push_back(box);

        equations.setPosition(_left + 20, height + 5);

        window.draw(equations);

        height += BOX_HEIGHT + VERTICAL_LINE_SPACING + BOTTOM_MARGIN;
    }
}
vector<sf::RectangleShape> &History::getEquationBoxes()
{
    return equationBoxes;
}

string &History::operator[](int index)
{
    return history[index];
}
