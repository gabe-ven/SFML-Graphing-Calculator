#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"

animate::animate(Graph_info *info) : sidebar(WORK_PANEL, SIDE_BAR), system(info), _info(info), history()

{
    tabPressed = false;
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    system = System(info);
    window.setFramerateLimit(240);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(2.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color(0, 225, 0));
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 5));

    invalidMessage = sf::Text("", font);
    invalidMessage.setCharacterSize(20);
    invalidMessage.setStyle(sf::Text::Bold);
    invalidMessage.setFillColor(sf::Color::Red);
    invalidMessage.setPosition(sf::Vector2f(1185, 750));

    cout << "animate instantiated successfully." << endl;

    history.loadEquations();
}

void animate::Draw()
{
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }

    sidebar.draw(window);
    history.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    window.draw(invalidMessage);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command, _info);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
}
void animate::render()
{
    window.clear(sf::Color(30, 30, 30));
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event)) // or waitEvent
    {
        system.Input(event);

        // check the type of the event...
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::R:
                sidebar[SB_KEY_PRESSED] = "RESET";
                command = 1;
                break;
            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "PAN LEFT";
                command = 2;
                break;
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "PAN RIGHT";
                command = 3;
                break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "PAN UP";
                command = 4;
                break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "PAN DOWN";
                command = 5;
                break;
            case sf::Keyboard::Period:
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                command = 6;
                break;

            case sf::Keyboard::Comma:
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                command = 7;
                break;
            case sf::Keyboard::Tab:
                sidebar[SB_KEY_PRESSED] = "INPUT";
                command = 8;
                tabPressed = true;
                break;
            case sf::Keyboard::P:
                sidebar[SB_KEY_PRESSED] = "POLAR";
                command = 9;
                break;
            case sf::Keyboard::C:
                sidebar[SB_KEY_PRESSED] = "CARTESIAN";
                command = 10;
                break;
            case sf::Keyboard::Enter:
                if (tabPressed)
                {
                    sidebar[SB_KEY_PRESSED] = "ENTER";
                    string equation = _info->get_equation();

                    if (equation == "0")
                    {
                        invalidMessage.setString("INVALID INPUT");
                        tabPressed = false;
                        return;
                    }

                    Tokenizer tokenizer;
                    tokenizer.tokenize(equation);
                    if (!tokenizer.invalid())
                    {
                        history.addHistory(equation);
                        invalidMessage.setString("");
                    }
                    else
                    {
                        invalidMessage.setString("INVALID INPUT");
                    }

                    tabPressed = false;
                }
                break;
            }

            break;

        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            // Do something with it if you need to...
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                                            mouse_pos_string(window);
            }
            else
            {
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                                            mouse_pos_string(window);

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < history.getEquationBoxes().size(); ++i)
                {
                    sf::RectangleShape &box = history.getEquationBoxes()[i];
                    if (box.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        string equation = history[i];
                        _info->set_equation(equation);
                        break;
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
