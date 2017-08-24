// SFML libraries
#include <SFML/Graphics.hpp>

#include <stdlib.h>

#include <ctime>
#include <chrono>
#include <iostream>

#include "../header/akarin.hpp"
#include "../header/akarin_math.hpp"

namespace Akarin
{

static bool initialized = false;

static int move_change_magnitude = 1;

static int akarin_height;
static int akarin_width;

static int radius = 40;
static int circle_sides_count = 20;
static int circle_x_origin_change = 0;
static int circle_y_origin_change = 0;

static int character_x_origin = 0;
static int character_y_origin = 0;

static int background_red_color = 255;
static int background_green_color = 200;
static int background_blue_color = 255;
static int background_alpha_value = 255;

static std::vector<sf::CircleShape> circle_array;
static std::vector<int> circle_x_origin_array;
static std::vector<int> circle_y_origin_array;

///////////////// DEBUGGING VARIABLES /////////////////////////////////////
static int statistics_negative_number_counter = 0;
static int statistics_zero_counter = 0;

static std::chrono::time_point<std::chrono::system_clock> debugging_time_start, debugging_time_end;

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
		character_y_origin--;
	}
	if (user_input.down.is_down)
	{
		std::cout << "down" << std::endl;
		circle_y_origin_change++;
		character_y_origin++;
	}
	if (user_input.right.is_down)
	{
		std::cout << "right" << std::endl;
		circle_x_origin_change++;
		character_x_origin++;
	}
	if (user_input.left.is_down)
	{
		std::cout << "left" << std::endl;
		circle_x_origin_change--;
		character_x_origin--;
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
	//std::cout << "creating circle" << std::endl;
	sf::CircleShape circle;
	circle.setRadius(10);

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
	debugging_time_start = std::chrono::system_clock::now();
	//std::cout << rand_with_negative(rand()) << ", " << rand_with_negative_2(rand()) << std::endl;
	//std::cout << RAND_MAX << std::endl;
	//std::cout << window->getSize().x << ", " << window->getSize().y << std::endl;
	//std::cout << "random:" << (rand() % akarin_height) << ", " << (rand() % akarin_width) << std::endl;

	// obtain the width and height from window
	akarin_width = window->getSize().x;
	akarin_height = window->getSize().y;

	// set the background color
	window->clear(sf::Color(
	                  background_red_color,
	                  background_green_color,
	                  background_blue_color,
	                  background_alpha_value
	              ));
	ParseUserInput(user_input);


	//createCircle();
	//draw the circlle
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
		/**

		int move_x = AkarinMath::rand_with_negative(6);
		int move_y = AkarinMath::rand_with_negative(5);

		if (move_x < 0)
		{
			statistics_negative_number_counter--;
		}
		else if (move_x > 0)
		{
			statistics_negative_number_counter++;
			std::cout << "positive!" << std::endl;
		}
		else
		{
			statistics_zero_counter++;
		}
		std::cout << "stats:" << statistics_negative_number_counter << ", " << statistics_zero_counter << std::endl;
		circle_array.at(circle_array_iterator).move(move_x, move_y);
		**/
		window->draw(circle_array.at(circle_array_iterator));
	}

	// Render the ground
	sf::RectangleShape ground;
	ground.setSize(sf::Vector2f(akarin_width, (akarin_height / 9)));
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(0, akarin_height - (akarin_height / 9));
	window->draw(ground);

	// Render the character
	sf::RectangleShape character;
	character.setSize(sf::Vector2f(30, 100));
	character.setFillColor(sf::Color::Black);
	character.setPosition(0 + character_x_origin, akarin_height - (akarin_height / 9) - 100 + character_y_origin);
	window->draw(character);


	/**
	PERFORMANCE DEBUGGING

	-- Figure out how to print out fps, rendering time (ms), and other information
	**/
	debugging_time_end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = debugging_time_end - debugging_time_start;
	std::cout << elapsed_seconds.count() << std::endl;
};
} //namespace Akarin