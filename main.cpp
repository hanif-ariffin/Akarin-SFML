#include <SFML/Graphics.hpp>
#include <iostream>

#include "akarin.hpp"

int main()
{
    int height = 800;
    int width = 600;

    /*
    create the window
    you can only declare one of these
    */
    sf::RenderWindow window(sf::VideoMode(height, width), "Akarin");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    /*
    Input struct
    */
    Akarin::GameInput user_input;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        /*
        Reset
        */
        user_input.up.is_down = false;
        user_input.down.is_down = false;
        user_input.left.is_down = false;
        user_input.right.is_down = false;
        user_input.space.is_down = false;

        user_input.up.was_released = false;
        user_input.down.was_released = false;
        user_input.left.was_released = false;
        user_input.right.was_released = false;
        user_input.space.was_released = false;

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
                    std::cout << "left key pressed" << std::endl;
                    //circle.move(-move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "right key pressed" << std::endl;
                    //circle.move(move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "left key pressed" << std::endl;
                    //circle.move(0, move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "right key pressed" << std::endl;
                    //circle.move(0, -move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    std::cout << "A key pressed" << std::endl;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::B)
                {
                    std::cout << "B key pressed" << std::endl;
                    //circle.setPointCount(circle_sides_count);
                }
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left)
                {
                    std::cout << "left key released" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    std::cout << "right key released" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "up key released" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "down key released" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    std::cout << "A key released" << std::endl;
                }
                else if (event.key.code == sf::Keyboard::B)
                {
                    std::cout << "B key released" << std::endl;
                }
                break;
            }
        }
        // clear the window with black color
        window.clear(sf::Color(255, 200, 255, 255));

        // Rendering here
        Akarin::RenderAndUpdate(&window, user_input);

        // end the current frame
        window.display();
    }

    return 0;
}