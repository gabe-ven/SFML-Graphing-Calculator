#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <iostream>
#include <fstream>
#include "graph.h"
#include "graph_info.h"
#include "coord_translator.h"
#include "random.h"
#include "constants.h"
#include "../../includes/tokenizer/tokenizer.h"

#include <SFML/Graphics.hpp>

using namespace std;

class System
{
public:
    System(Graph_info *info);
    void set_info(Graph_info *info);
    void Step(int command, Graph_info *info); // Calls graph::update()
    void Draw(sf::RenderWindow &window);      // Calls graph::draw()
    void Input(sf::Event event);
    void createInputBox();
    void saveToFile(const string &equation);

private:
    Graph _g;
    Graph_info *_info;

    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::Font font;
    string userInput;
    bool inputOn;
    bool isPolar;
};

#endif // SYSTEM_H
