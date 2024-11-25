#include "system.h"
#include "random.h"
#include "constants.h"
#include "graph_info.h"
#include <iostream>
#include <vector>

System::System(Graph_info *info) : _g(info) // pass info to graph
{
    _info = info;
    inputActive = false;
    set_info(info);
}

void System::set_info(Graph_info *info)
{
    _info = info;
    _g.update(info); // call update in graph
}

void System::Step(int command, Graph_info *info)
{
    if (command == 4)
    {
    }
    else if (command == 6)
    {
    }
    else if (command == 7)
    {
        inputActive = !inputActive;

        if (inputActive)
        {
            createInputBox();
        }
    }
    _g.update(info);
}

// draw graph here

void System::Draw(sf::RenderWindow &window)
{
    _g.Draw(window);

    if (inputActive)
    {
        window.draw(inputBox);
        window.draw(inputText);
    }
}

void System::HandleInput(sf::Event event)
{
    if (inputActive && event.type == sf::Event::TextEntered)
    {
        string currentString = inputText.getString();

        if (event.text.unicode < 128)
        {
            if (event.text.unicode == 8) // delete
            {
                if (currentString.length() > 4) // length is greater than "y = "
                {
                    currentString.pop_back();
                    inputText.setString(currentString);
                }
            }
            else
            {
                if (currentString.length() < 4)
                {
                    currentString = "y = " + (char)event.text.unicode;
                }
                else
                {
                    currentString += (char)event.text.unicode;
                }
                inputText.setString(currentString);
            }
        }
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            string equation = inputText.getString();
            equation = equation.substr(4);

            _info->set_equation(equation);

            _g.update(_info);

            inputActive = false;
        }
    }
}
void System::createInputBox()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr << "Error loading font!" << endl;
    }

    inputBox.setSize(sf::Vector2f(300, 30));
    inputBox.setFillColor(sf::Color(40, 40, 40));
    inputBox.setPosition(400, 40);
    inputBox.setOutlineColor(sf::Color::Green);
    inputBox.setOutlineThickness(2);

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Green);
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y);
    inputText.setString("y = ");
}
