#include <SFML/Graphics.hpp>
#include <iostream>

#include "akarin.hpp"

int main()
{
    int height = 500;
    int width = 700;

    /*
    create the window
    you can only declare one of these
    */
    sf::RenderWindow window(sf::VideoMode(width, height), "Akarin");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    /*
    Input struct
    */
    Akarin::UserInput user_input;
    /*
    Reset everything to false
    */
    user_input.up.is_down = false;
    user_input.down.is_down = false;
    user_input.left.is_down = false;
    user_input.right.is_down = false;
    user_input.q.is_down = false;
    user_input.w.is_down = false;
    user_input.e.is_down = false;
    user_input.r.is_down = false;
    user_input.space.is_down = false;

    user_input.up.was_released = false;
    user_input.down.was_released = false;
    user_input.left.was_released = false;
    user_input.right.was_released = false;
    user_input.q.was_released = false;
    user_input.w.was_released = false;
    user_input.e.was_released = false;
    user_input.r.was_released = false;
    user_input.space.was_released = false;
    // run the program as long as the window is open
    while (window.isOpen())
    {
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
                    //std::cout << "left key pressed" << std::endl;
                    user_input.left.is_down = true;
                    //circle.move(-move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    //std::cout << "right key pressed" << std::endl;
                    user_input.right.is_down = true;
                    //circle.move(move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    //std::cout << "left key pressed" << std::endl;
                    user_input.down.is_down = true;
                    //circle.move(0, move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    //std::cout << "right key pressed" << std::endl;
                    user_input.up.is_down = true;
                    //circle.move(0, -move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    //std::cout << "A key pressed" << std::endl;
                    user_input.q.is_down = true;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.w.is_down = true;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::E)
                {
                    //std::cout << "A key pressed" << std::endl;
                    user_input.e.is_down = true;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.r.is_down = true;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.space.is_down = true;
                    //circle.setPointCount(circle_sides_count);
                }
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left)
                {
                    //std::cout << "left key pressed" << std::endl;
                    user_input.left.is_down = false;
                    //circle.move(-move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    //std::cout << "right key pressed" << std::endl;
                    user_input.right.is_down = false;
                    //circle.move(move_change_magnitude, 0);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    //std::cout << "left key pressed" << std::endl;
                    user_input.down.is_down = false;
                    //circle.move(0, move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    //std::cout << "right key pressed" << std::endl;
                    user_input.up.is_down = false;
                    //circle.move(0, -move_change_magnitude);
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    //std::cout << "A key pressed" << std::endl;
                    user_input.q.is_down = false;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.w.is_down = false;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::E)
                {
                    //std::cout << "A key pressed" << std::endl;
                    user_input.e.is_down = false;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.r.is_down = false;
                    //circle.setPointCount(circle_sides_count);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    //std::cout << "B key pressed" << std::endl;
                    user_input.space.is_down = false;
                    //circle.setPointCount(circle_sides_count);
                }
                break;
            }
        }
        // clear the window with black color
        //window.clear(sf::Color(0, 0, 0, 0));

        // Rendering here
        Akarin::RenderAndUpdate(&window, user_input);

        // end the current frame
        window.display();
    }

    return 0;
}