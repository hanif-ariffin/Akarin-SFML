// SFML libraries
#if LINUX_BUILD
//Nothing SFML is provided by the compiler
#else

#include <SFML/Graphics.hpp>

#endif

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <math.h>
#include <chrono>

#include "engine.hpp"
#include "debugging_tools.hpp"

#define GRID_INTERVAL 100
#define GRID_SIZE 5
namespace Engine {

    bool first_render = true;
    int first_render_original_window_width = -1;
    int first_render_original_window_height = -1;
    int rgb_max_value = 254;
    int rgb_min_value = 10;
    int scale_from_startup_x = 1;
    int scale_from_startup_y = 1;
    std::vector <ObjectWithWeight> tail_array;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Image image;

    sf::RectangleShape center_crosshair_x(sf::Vector2f(50, 10));
    sf::RectangleShape center_crosshair_y(sf::Vector2f(10, 50));

    sf::Font font;

    DebuggingInformation DEBUGGING_INFORMATION{};

    ObjectWithWeight character;
    int character_x_origin = 0;
    int character_y_origin = 0;

    int camera_x_origin = character_x_origin;
    int camera_y_origin = character_y_origin;
    int character_velocity_x = 0;
    int character_velocity_y = 0;
    int character_velocity_max = 50;

    int background_red_color = 0;
    bool background_red_color_going_up = true;
    int background_green_color = 0;
    bool background_green_color_going_up = true;
    int background_blue_color = 0;
    bool background_blue_color_going_up = true;
    int background_alpha_color = 0;
    bool background_alpha_color_going_up = true;

    int current_rotation = 0;

    void AddRectaglesToTail() {
        ObjectWithWeight rectangle_with_height;
        rectangle_with_height.circle.setRadius(character_velocity_max);
        rectangle_with_height.circle.setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
        rectangle_with_height.position_x = character_x_origin;
        rectangle_with_height.position_y = character_y_origin;
        current_rotation %= 360;

        tail_array.push_back(rectangle_with_height);
    }

    void RenderGrid() {
        if ((camera_x_origin % GRID_INTERVAL) == 0) {
            std::cout << "creating horizontal grid camera_x:" << camera_x_origin << std::endl;
            ObjectWithWeight horizontal_grid;
            horizontal_grid.circle.setRadius(GRID_SIZE);
            horizontal_grid.circle.setFillColor(sf::Color(255, 255, 255));
            horizontal_grid.position_x = camera_x_origin + (first_render_original_window_width / 2);
            horizontal_grid.position_y = camera_y_origin;
            tail_array.push_back(horizontal_grid);
        }
        if ((camera_y_origin & GRID_INTERVAL) == 0) {
            std::cout << "creating vertical grid camera_y:" << camera_x_origin << std::endl;
            ObjectWithWeight horizontal_grid;
            horizontal_grid.circle.setRadius(GRID_SIZE);
            horizontal_grid.circle.setFillColor(sf::Color(255, 255, 255));
            horizontal_grid.position_x = camera_x_origin;
            horizontal_grid.position_y = camera_y_origin + (first_render_original_window_height / 2);
            tail_array.push_back(horizontal_grid);
        }
    }

    void UpdateCharacterPosition() {
        character.position_x = character_x_origin;
        character.position_y = character_y_origin;
    };

    void UpdateCameraPosition() {
        camera_x_origin = character_x_origin;
        camera_y_origin = character_y_origin;
    };

    void ParseInput(UserInput *user_input) {
        if (user_input->up.is_down) /// UP
        {
            if (character_velocity_y < character_velocity_max) {
                character_velocity_y++;
            }
            character_y_origin += character_velocity_y;

            if (background_red_color_going_up) {
                background_red_color++;
            } else {
                background_red_color--;
            }
            if (background_red_color > rgb_max_value) {
                background_red_color_going_up = false;
            } else if (background_red_color < rgb_min_value) {
                background_red_color_going_up = true;
            }
        } else {
            if (character_velocity_y > 0) {
                character_y_origin += character_velocity_y;
                character_velocity_y--;
            }
        }

        if (user_input->down.is_down) // DOWN
        {
            if (character_velocity_y > -character_velocity_max) {
                character_velocity_y--;
            }
            character_y_origin += character_velocity_y;

            if (background_green_color_going_up) {
                background_green_color++;
            } else {
                background_green_color--;
            }
            if (background_green_color > rgb_max_value) {
                background_green_color_going_up = false;
            } else if (background_green_color < rgb_min_value) {
                background_green_color_going_up = true;
            }
        } else {
            if (character_velocity_y < 0) {
                character_y_origin += character_velocity_y;
                character_velocity_y++;
            }
        }

        if (user_input->left.is_down) // LEFT
        {

            if (character_velocity_x > -character_velocity_max) {
                character_velocity_x--;
            }
            character_x_origin += character_velocity_x;

            if (background_alpha_color_going_up) {
                background_alpha_color++;
            } else {
                background_alpha_color--;
            }
            if (background_alpha_color > rgb_max_value) {
                background_alpha_color_going_up = false;
            } else if (background_alpha_color < rgb_min_value) {
                background_alpha_color_going_up = true;
            }
        } else {
            if (character_velocity_x < 0) {
                character_x_origin += character_velocity_x;
                character_velocity_x++;
            }
        }

        if (user_input->right.is_down) // RIGHT
        {
            if (character_velocity_x < character_velocity_max) {
                character_velocity_x++;
            }
            character_x_origin += character_velocity_x;

            if (background_blue_color_going_up) {
                background_blue_color++;
            } else {
                background_blue_color--;
            }
            if (background_blue_color > rgb_max_value) {
                background_blue_color_going_up = false;
            } else if (background_blue_color < rgb_min_value) {
                background_blue_color_going_up = true;
            }
        } else {
            if (character_velocity_x > 0) {
                character_x_origin += character_velocity_x;
                character_velocity_x--;
            }
        }
        if (user_input->q.is_down) // RIGHT
        {
            std::cout << "Q" << std::endl;
        }
        if (user_input->up.is_down || user_input->down.is_down || user_input->left.is_down ||
            user_input->right.is_down) {
        };
    };

    void TrailEffects(void) {
        for (int tail_array_iterator = 0; tail_array_iterator < tail_array.size(); tail_array_iterator++) {
            if (tail_array.at(tail_array_iterator).circle.getRadius() == 0
                    ) {
                tail_array.erase(tail_array.begin() + tail_array_iterator);
            } else {
                tail_array.at(tail_array_iterator).circle.setRadius(
                        tail_array.at(tail_array_iterator).circle.getRadius() - 1);
                int screen_offset_x =
                        tail_array.at(tail_array_iterator).position_x + (first_render_original_window_width / 2) -
                        camera_x_origin - (tail_array.at(tail_array_iterator).circle.getRadius() / 2);
                int screen_offset_y =
                        -tail_array.at(tail_array_iterator).position_y + (first_render_original_window_height / 2) +
                        camera_y_origin - (tail_array.at(tail_array_iterator).circle.getRadius() / 2);

#if DEBUGGING_CAMERA_RENDERING
                std::cout << offset_x << ", " << offset_y << " && "
                          << original_width << " , " << original_height << " && "
                          << tail_array.at(tail_array_iterator).position_x << ", " << camera_x_origin << " && "
                          << tail_array.at(tail_array_iterator).position_y << ", " << camera_y_origin << std::endl;
#endif
                tail_array.at(tail_array_iterator).circle.setPosition(screen_offset_x, screen_offset_y);
            }
        }
    };

    void RenderObjects(sf::RenderWindow *window) {
        for (int tail_array_iterator = 0; tail_array_iterator < tail_array.size(); tail_array_iterator++) {
            window->draw(tail_array.at(tail_array_iterator).circle);
        }
    };

    void RenderAndUpdate(sf::RenderWindow *window, UserInput *user_input, TimePassed *given_time_passed) {
        if (first_render) {
            if (!image.loadFromFile("default_pic.png")) {
                std::cout << "Unable to load image for sprite" << std::endl;
            } else {
                std::cout << "Image for sprite successfully loaded" << std::endl;
            }

            if (!font.loadFromFile("courier_new.ttf")) {
                std::cout << "Unable to load font for debugging" << std::endl;
            } else {
                std::cout << "Font for debugging successfully loaded" << std::endl;
            }


            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            window->draw(sprite);
        }
        if (false) {
            first_render_original_window_width = window->getSize().x;
            first_render_original_window_height = window->getSize().y;

#if DEBUGGING_WITH_CROSSHAIR
            center_crosshair_x.setFillColor(sf::Color::Green);
            center_crosshair_y.setFillColor(sf::Color::Green);

            center_crosshair_x.setPosition((window->getSize().x / 2) - (center_crosshair_x.getSize().x / 2), (window->getSize().y / 2) - (center_crosshair_x.getSize().y / 2));
            center_crosshair_y.setPosition((window->getSize().x / 2) - (center_crosshair_y.getSize().x / 2), (window->getSize().y / 2) - (center_crosshair_y.getSize().y / 2));
#endif

            first_render = false;
        }

        window->
                clear(sf::Color(
                background_red_color,
                background_green_color,
                background_blue_color,
                background_alpha_color)
        );

        AddRectaglesToTail();

        if ((first_render_original_window_height != window->

                        getSize()

                .x) ||
            (first_render_original_window_width != window->

                            getSize()

                    .y)) {

        }

        TrailEffects();

        RenderObjects(window);
        ParseInput(user_input);

        UpdateCameraPosition();

        UpdateCharacterPosition();

#if DEBUGGIND_CAMERA_RENDERING
        std::cout << (camera_x_origin - old_camera_x_origin) << ", " << (camera_y_origin - old_camera_y_origin) << std::endl;
#endif
        sprite.
                setPosition((first_render_original_window_height
                             / 2) - (image.

                                            getSize()

                                             .x / 2),
                            (first_render_original_window_width / 2) - (image.

                                            getSize()

                                                                                .y / 2));

#if DEBUGGING_TRYING_OUT_CONVEX_SHAPE
        sf::ConvexShape polygon;
        int polygon_x = window.getSize().x / 4;
        int polygon_y = window.getSize().y / 2;
        int polygon_size = 20;
        int start_coordinate = 50;
        polygon.setPointCount(3);

        polygon.setPoint(0, sf::Vector2f(50, -start_coordinate));
        polygon.setPoint(1, sf::Vector2f(start_coordinate, start_coordinate));
        polygon.setPoint(2, sf::Vector2f(-start_coordinate, start_coordinate));
        start_coordinate++;
        polygon.setOutlineColor(sf::Color::White);
        polygon.setOutlineThickness(0);
        polygon.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        polygon.setPosition(polygon.getPosition().x + 1, polygon.getPosition().y + 1);
#endif

#if DEBUGGING_WITH_CROSSHAIR
        window->draw(center_crosshair_x);
        window->draw(center_crosshair_y);
#endif

        std::string resulting_string = "DEBUGGING INFORMATION: \n";
        std::ostringstream ostr1, ostr2, ostr3, ostr4;

        ostr1 << given_time_passed->
                seconds;
        resulting_string += (ostr1.

                str()

                             + " seconds \n");

        ostr2 << given_time_passed->
                milliseconds;
        resulting_string += (ostr2.

                str()

                             + " milliseconds \n");

        ostr3 <<
              character_velocity_x;
        resulting_string += ("(" + ostr3.

                str()

                             + ", ");

        ostr4 <<
              character_velocity_y;
        resulting_string += (ostr4.

                str()

                             + ") pixels / render");

#if UNUSED_USING_DEBUGGING_INFORMATION_STRUCT
        DEBUGGING_INFORMATION.program_name = "Akarin-SFML";
        DEBUGGING_INFORMATION.render_time = "";
        DEBUGGING_INFORMATION.render_time += given_time_passed->seconds;
        DEBUGGING_INFORMATION.render_time += " seconds ";
        DEBUGGING_INFORMATION.render_time += given_time_passed->milliseconds;
        DEBUGGING_INFORMATION.render_time += " milliseconds ";
#endif

        sf::Text text(resulting_string, font);
        text.setCharacterSize(30);
        text.
                setStyle(sf::Text::Bold);

        int text_color_red, text_color_green, text_color_blue;
        if (background_red_color >= 128) {
            text_color_red = 0;
        } else {
            text_color_red = 255;
        }
        if (background_green_color >= 128) {
            text_color_green = 0;
        } else {
            text_color_green = 255;
        }
        if (background_blue_color >= 128) {
            text_color_blue = 0;
        } else {
            text_color_blue = 255;
        }
        window->
                draw(text);
    };
}