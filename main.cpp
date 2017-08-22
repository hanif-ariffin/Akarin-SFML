#include <SFML/Graphics.hpp>
#include "akarin.h"
#include <iostream>

int main()
{
    /*
    create the window
    you can only declare one of these
    */
    int height = 800;
    int width = 600;
    Akarin::GameInput old_game_input;
    Akarin::GameInput new_game_input;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        /*
        Reset
        */
        old_game_input = new_game_input;
        game_input = {false};

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // "close requested" event: we close the window
            case sf::Event::Closed:
                std::cout << "closing application" << std::endl;
                window.close();
                break;

            case sf::Event::Resized:
                std::cout << "width: " << event.size.width << " height: " << event.size.height << std::endl;
                height = event.size.height;
                width = event.size.width;
                break;

            case sf::Event::LostFocus:
                std::cout << "lost focus" << std::endl;
                break;

            case sf::Event::GainedFocus:
                std::cout << "gained focus" << std::endl;
                break;

            /**
            A beter implementation of 'holding' a key is to check if the key is released instead of using the repeated trigger that would be limited by the device
            **/
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    std::cout << "left key" << std::endl;
                    //circle.move(-move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "right key" << std::endl;
                    //circle.move(move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "left key" << std::endl;
                    //circle.move(0, move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "right key" << std::endl;
                    //circle.move(0, -move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    std::cout << "A current count side:" << ++circle_sides_count << std::endl;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::B)
                {
                    std::cout << "B current count side:" << --circle_sides_count << std::endl;
                    //circle.setPointCount(circle_sides_count);
                }
                break;
            }
        }
        // clear the window with black color
        window.clear(sf::Color(255, 200, 255, 255));

        Akarin::RenderAndUpdate(window);
        // end the current frame
        window.display();
    }

    return 0;
}