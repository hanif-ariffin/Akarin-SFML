#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <chrono>

//#include "engine.hpp"

#define DEFAULT_ICON "default_pic.png"
#define DEFAULT_MUSIC "default_music.ogg"
#define MATH_CONSTANT_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

int main() {

    sf::RenderWindow window(sf::VideoMode(400, 400), "Akarin (SFML)");

    sf::Image icon;
    if (!icon.loadFromFile(DEFAULT_ICON)) {
        std::cout << "Unable to load app icon" << std::endl;
    } else {
        std::cout << "Image successfully loaded" << std::endl;
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    /**
    Engine::UserInput user_input;
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

  **//**

    sf::Music music;
    if (!music.openFromFile(DEFAULT_MUSIC)) {
        std::cout << "Unable to load music" << std::endl;
    } else {
        std::cout << "Music loaded successfully" << std::endl;
        // Play the music
        music.play();
    }**/
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    /**
    if (false) {
        Engine::TimePassed systemtime_time_between_rendering = {0, 0};

        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        sf::Event event;
        while (false && window.pollEvent(event)) {
            switch (event.type) {
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

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        std::cout << "the escape key was pressed" << std::endl;
                        std::cout << "control:" << event.key.control << std::endl;
                        std::cout << "alt:" << event.key.alt << std::endl;
                        std::cout << "shift:" << event.key.shift << std::endl;
                        std::cout << "system:" << event.key.system << std::endl;
                        window.close();
                    } else if (event.key.code == sf::Keyboard::Left) {
                        //std::cout << "left key pressed" << std::endl;
                        user_input.left.is_down = true;
                        //circle.move(-move_change_magnitude, 0);
                    } else if (event.key.code == sf::Keyboard::Right) {
                        //std::cout << "right key pressed" << std::endl;
                        user_input.right.is_down = true;
                        //circle.move(move_change_magnitude, 0);
                    } else if (event.key.code == sf::Keyboard::Down) {
                        //std::cout << "left key pressed" << std::endl;
                        user_input.down.is_down = true;
                        //circle.move(0, move_change_magnitude);
                    } else if (event.key.code == sf::Keyboard::Up) {
                        //std::cout << "right key pressed" << std::endl;
                        user_input.up.is_down = true;
                        //circle.move(0, -move_change_magnitude);
                    } else if (event.key.code == sf::Keyboard::Q) {
                        //std::cout << "A key pressed" << std::endl;
                        user_input.q.is_down = true;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::W) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.w.is_down = true;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::E) {
                        //std::cout << "A key pressed" << std::endl;
                        user_input.e.is_down = true;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::R) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.r.is_down = true;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::Space) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.space.is_down = true;
                        //circle.setPointCount(circle_sides_count);
                    }
                    break;

                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Left) {
                        //std::cout << "left key pressed" << std::endl;
                        user_input.left.is_down = false;
                        //circle.move(-move_change_magnitude, 0);
                    } else if (event.key.code == sf::Keyboard::Right) {
                        //std::cout << "right key pressed" << std::endl;
                        user_input.right.is_down = false;
                        //circle.move(move_change_magnitude, 0);
                    } else if (event.key.code == sf::Keyboard::Down) {
                        //std::cout << "left key pressed" << std::endl;
                        user_input.down.is_down = false;
                        //circle.move(0, move_change_magnitude);
                    } else if (event.key.code == sf::Keyboard::Up) {
                        //std::cout << "right key pressed" << std::endl;
                        user_input.up.is_down = false;
                        //circle.move(0, -move_change_magnitude);
                    } else if (event.key.code == sf::Keyboard::Q) {
                        //std::cout << "A key pressed" << std::endl;
                        user_input.q.is_down = false;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::W) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.w.is_down = false;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::E) {
                        //std::cout << "A key pressed" << std::endl;
                        user_input.e.is_down = false;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::R) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.r.is_down = false;
                        //circle.setPointCount(circle_sides_count);
                    } else if (event.key.code == sf::Keyboard::Space) {
                        //std::cout << "B key pressed" << std::endl;
                        user_input.space.is_down = false;
                        //circle.setPointCount(circle_sides_count);
                    }
                    break;
            }
        }

        Engine::RenderAndUpdate(&window, &user_input, &systemtime_time_between_rendering);
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        std::chrono::duration < int, std::milli > time_span = std::chrono::duration_cast < std::chrono::duration < int,
                std::milli >> (t2 - t1);
        systemtime_time_between_rendering.milliseconds = time_span.count();

        window.display();
    }

    **/
    return 0;
}
