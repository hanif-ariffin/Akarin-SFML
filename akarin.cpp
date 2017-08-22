#include "akarin.hpp"
#include <iostream>

namespace Akarin {

static int move_change_magnitude = 1;

static int height = 800;
static int width = 600;

static int radius = 40;
static int circle_sides_count = 20;

static int background_red_color = 0;
static int background_green_color = 0;
static int background_blue_color = 0;
static int background_alpha_value = 0;

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
	}
	if (user_input.down.is_down)
	{
		std::cout << "down" << std::endl;
	}
	if (user_input.right.is_down)
	{
		std::cout << "right" << std::endl;
	}
	if (user_input.left.is_down)
	{
		std::cout << "left" << std::endl;
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
	}
}

void RenderAndUpdate(
    sf::RenderWindow *window,
    UserInput user_input
) {

	ParseUserInput(user_input);
	// Set background color
	window->clear(sf::Color(
	                  background_red_color,
	                  background_green_color,
	                  background_blue_color,
	                  background_alpha_value
	              ));

	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(
	                                 120,
	                                 50
	                             ));

	// change the size to 100x100
	rectangle.setSize(sf::Vector2f(
	                      100,
	                      100
	                  ));

	// define a circle with radius = 200
	sf::CircleShape circle(radius);

	// change the radius to 40
	//circle.setRadius(40);
	circle.setPosition(
	    (height / 2 ) - (radius),
	    (width / 2)  - (radius)
	);

	// change the number of sides (points) to 100
	circle.setPointCount(circle_sides_count);

	window->draw(circle);
};
}
