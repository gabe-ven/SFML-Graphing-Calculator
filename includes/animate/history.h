#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "constants.h"

using namespace std;

class History
{
public:
    History();
    void draw(sf::RenderWindow &window);
    void addHistory(const string &equation);
    void loadEquations();
    vector<sf::RectangleShape> &getEquationBoxes();
    string &operator[](int index);

private:
    float _left;
    float _width;
    sf::RectangleShape rect;
    sf::Text equations;
    vector<string> history;
    vector<sf::RectangleShape> equationBoxes;
    sf::Font font;
};
