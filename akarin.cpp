#include "akarin.hpp"
#include <stdlib.h>
#include <iostream>

namespace Akarin {

static bool initialized = false;

static int move_change_magnitude = 1;

static int akarin_height = 900;
static int akarin_width = 1800;

static int radius = 40;
static int circle_sides_count = 20;
static int circle_x_origin_change = 0;
static int circle_y_origin_change = 0;

static int background_red_color = 0;
static int background_green_color = 0;
static int background_blue_color = 0;
static int background_alpha_value = 0;

static std::vector<sf::CircleShape> circle_array;
static std::vector<int> circle_x_origin_array;
static std::vector<int> circle_y_origin_array;

/*
Note:
For the meantime we will parse only through pressed keys event -- DONE
We will be working on utilizing released key some time after this -- DONE
Also write a better tool for debugging

first have a bool that check if there is any pressed button
then print std::endl << /pressed_buttons << std::endl

for better reading and saves space, actually
*/
void ParseUserInput(UserInput user_input)
{
	if (user_input.up.is_down)
	{
		std::cout << "up" << std::endl;
		circle_y_origin_change--;
	}
	if (user_input.down.is_down)
	{
		std::cout << "down" << std::endl;
		circle_y_origin_change++;
	}
	if (user_input.right.is_down)
	{
		std::cout << "right" << std::endl;
		circle_x_origin_change++;
	}
	if (user_input.left.is_down)
	{
		std::cout << "left" << std::endl;
		circle_x_origin_change--;
	}
	if (user_input.q.is_down)
	{
		std::cout << "q" << std::endl;
		background_red_color++;
	}
	if (user_input.w.is_down)
	{
		std::cout << "w" << std::endl;
		background_green_color++;
	}
	if (user_input.e.is_down)
	{
		std::cout << "e" << std::endl;
		background_blue_color++;
	}
	if (user_input.r.is_down)
	{
		std::cout << "r" << std::endl;
		background_alpha_value++;
	}
	if (user_input.space.is_down)
	{
		std::cout << "space" << std::endl;
		createCircle();
	}
}

void createCircle()
{
	sf::CircleShape circle(radius);

	int circle_x_origin = (rand() % akarin_width) - radius;
	int circle_y_origin = (rand() % akarin_height) - radius;
	circle.setPosition(
	    circle_x_origin,
	    circle_y_origin
	);
	circle.setPointCount(circle_sides_count);
	circle.setFillColor(sf::Color(
	                        rand() % 256,
	                        rand() % 256,
	                        rand() % 256,
	                        rand() % 256
	                    ));

	circle_array.push_back(circle);
};

void RenderAndUpdate(
    sf::RenderWindow *window,
    UserInput user_input
) {
	//std::cout << "random:" << (rand() % akarin_height) << ", " << (rand() % akarin_width) << std::endl;
	// Set background color
	window->clear(sf::Color(
	                  background_red_color,
	                  background_green_color,
	                  background_blue_color,
	                  background_alpha_value
	              ));
	ParseUserInput(user_input);

	//draw the circle
	for (int circle_array_iterator = 0; circle_array_iterator < circle_array.size(); circle_array_iterator++)
	{
		if (user_input.up.is_down)
		{
			circle_array.at(circle_array_iterator).move(0, -5);
		}
		if (user_input.down.is_down)
		{
			circle_array.at(circle_array_iterator).move(0, 5);
		}
		if (user_input.left.is_down)
		{
			circle_array.at(circle_array_iterator).move(-5, 0);
		}
		if (user_input.right.is_down)
		{
			circle_array.at(circle_array_iterator).move(5, 0);
		}

		circle_array.at(circle_array_iterator).move((rand() % 3) - 1, (rand() % 3) - 1);
		window->draw(circle_array.at(circle_array_iterator));
	}
};
}
