#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "graph.h"
#include "graph_info.h"
#include <SFML/Graphics.hpp>

using namespace std;
class System
{
public:
    System(Graph_info *info);
    void set_info(Graph_info *info);
    void Step(int command, Graph_info *info); // Calls graph::update()
    void Draw(sf::RenderWindow &window);      // Calls graph::draw()
    void HandleInput(sf::Event event);
    void createInputBox();

private:
    Graph _g;
    Graph_info *_info;

    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::Font font;
    string userInput;
    bool inputActive;
};

#endif // SYSTEM_H
