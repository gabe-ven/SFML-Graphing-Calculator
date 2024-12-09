#include "system.h"

// g++ includes/animate/animate.cpp includes/animate/sidebar.cpp includes/animate/system.cpp includes/animate/random.cpp includes/animate/graph.cpp includes/animate/graph_info.cpp includes/animate/plot.cpp includes/token/operator.cpp includes/token/function.cpp includes/shunting_yard/shunting_yard.cpp includes/rpn/rpn.cpp main.cpp includes/animate/coord_translator.cpp includes/tokenizer/tokenizer.cpp  -I/opt/homebrew/Cellar/sfml/2.6.1/include -o prog -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

System::System(Graph_info *info) : _g(info) // pass info to graph
{
    _info = info;
    inputOn = false;
    set_info(info);
}

void System::set_info(Graph_info *info)
{
    _info = info;
    _g.update(info); // call update in graph
}

void System::Step(int command, Graph_info *info)
{
    _info = info;
    sf::Vector2f origin = _info->get_origin();
    sf::Vector2f domain = _info->get_domain();
    sf::Vector2f window_dimensions = _info->get_window_dimensions();

    double domain_range = domain.y - domain.x;

    if (command == 1) // reset
    {
        _info->set_origin(WORK_PANEL / 2, SCREEN_HEIGHT / 2);
        _info->set_domain(-5, 5);
    }
    else if (command == 2 || command == 3) // pan left / right
    {
        double shift = 20.0;

        double domain_shift = (domain_range / window_dimensions.x) * shift;

        if (command == 2) // pan left
        {
            _info->set_origin(origin.x + shift, origin.y);
            _info->set_domain(domain.x - domain_shift, domain.y - domain_shift);
        }
        else if (command == 3) // pan right
        {
            _info->set_origin(origin.x - shift, origin.y);
            _info->set_domain(domain.x + domain_shift, domain.y + domain_shift);
        }
    }

    else if (command == 4 || command == 5) // pan up / down
    {
        double shift = 20.0;

        if (command == 4) // pan up
        {
            _info->set_origin(origin.x, origin.y - shift);
        }
        else if (command == 5) // pan down
        {
            _info->set_origin(origin.x, origin.y + shift);
        }
    }
    else if (command == 6 || command == 7) // zoom in / out
    {
        double zoom_factor;

        if (command == 6) // zoom in
        {
            zoom_factor = 0.95;
        }
        else if (command == 7) // zoom out
        {
            zoom_factor = 1.05;
        }

        double graph_center = (domain.x + domain.y) / 2.0;
        double new_domain_range = domain_range * zoom_factor;

        double new_domain_start = graph_center - new_domain_range / 2.0;
        double new_domain_end = graph_center + new_domain_range / 2.0;

        _info->set_domain(new_domain_start, new_domain_end);

        double screen_center_x = window_dimensions.x / 2.0;
        double screen_center_y = window_dimensions.y / 2.0;

        double new_origin_x = origin.x + (screen_center_x - origin.x) * (((zoom_factor) * 0.9975) - 1.0);
        double new_origin_y = origin.y + (screen_center_y - origin.y) * (zoom_factor - 1.0);

        _info->set_origin(new_origin_x, new_origin_y);
    }

    else if (command == 8) // input box
    {
        inputOn = !inputOn; // switch input

        if (inputOn)
        {
            createInputBox();
        }
    }
    else if (command == 9) // toggle polar
    {
        _info->set_polar(true);
    }
    else if (command == 10) // toggle cartesian
    {
        _info->set_polar(false);
    }

    _g.update(info);
}

// draw graph here

void System::Draw(sf::RenderWindow &window)
{
    _g.Draw(window);

    if (inputOn)
    {
        window.draw(inputBox);
        window.draw(inputText);
    }
}

void System::Input(sf::Event event)
{
    if (inputOn && event.type == sf::Event::TextEntered)
    {
        string currentString = inputText.getString();

        if (event.text.unicode < 128)
        {
            if (event.text.unicode == 8) // delete key
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
                    currentString = "y = " + event.text.unicode;
                }
                else
                {
                    currentString += event.text.unicode;
                }
                inputText.setString(currentString);
            }
        }
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter) // this marks submitting the function
        {
            string equation = inputText.getString();
            equation = equation.substr(4); // after the "y = "

            Tokenizer tokenizer;
            tokenizer.tokenize(equation);

            if (!tokenizer.invalid())
            {
                _info->set_equation(equation); // set new equation
                saveToFile(equation);          // write equation to file
            }
            else
            {
                _info->set_equation("0");
            }
            inputOn = false;
            _g.update(_info); // update info
        }
    }
}
void System::createInputBox()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr << "Error loading font!" << endl;
    }

    inputBox.setSize(sf::Vector2f(300, 40));
    inputBox.setFillColor(sf::Color(40, 40, 40));
    inputBox.setPosition(420, 50);
    inputBox.setOutlineColor(sf::Color::Green);
    inputBox.setOutlineThickness(2);

    inputText.setFont(font);
    inputText.setCharacterSize(25);
    inputText.setFillColor(sf::Color::Green);
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 5);
    inputText.setString("y = ");
}

void System::saveToFile(const string &equation)
{
    ofstream file("functions.txt", ios::app);

    if (!file.is_open())
    {
        return;
    }

    file << equation << endl;
    file.close();
}
