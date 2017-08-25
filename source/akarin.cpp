// SFML libraries
#include <SFML/Graphics.hpp>

#include <stdlib.h>

#include <ctime>
#include <chrono>
#include <iostream>

#include "../header/akarin.hpp"
#include "../header/akarin_math.hpp"
//#include "../header/akarin_atom.hpp"

namespace Akarin
{

class Atom
{
public:
	sf::RectangleShape shape;
	int position_x;
	int position_y;

	Atom(int red, int green, int blue, int given_position_x, int given_position_y)
	{
		shape.setFillColor(sf::Color(red, green, blue));
		shape.setSize(sf::Vector2f(20, 20));
		position_x = given_position_x;
		position_y = given_position_y;
	}

	Atom()
	{
		shape.setFillColor(sf::Color(0, 0, 0));
		shape.setSize(sf::Vector2f(100, 100));
		position_x = 0;
		position_y = 0;
	}
};

// Global Variables
static std::chrono::time_point<std::chrono::system_clock> game_current_time;
static int akarin_height;
static int akarin_width;

// World variables
std::vector<Atom> world_atom;

// Variables for each circles
static int radius = 40;
static int circle_sides_count = 20;
static int circle_x_origin_change = 0;
static int circle_y_origin_change = 0;

// Variables for holding all the created circles
static std::vector<sf::CircleShape> circle_array;
static std::vector<int> circle_x_origin_array;
static std::vector<int> circle_y_origin_array;

// Variables for the character
static int camera_x_origin = 0;
static int camera_y_origin = 0;
static bool ask_jump = false;
static bool is_jumping = false;
static int character_x_offset; // since we want to center character on the x axis
static int character_y_offset; // since we want to place character lower on the y axis

static std::chrono::time_point<std::chrono::system_clock> time_jump_start;

// Variables for the background
static int background_red_color = 255;
static int background_green_color = 200;
static int background_blue_color = 255;
static int background_alpha_value = 255;

///////////////// DEBUGGING VARIABLES /////////////////////////////////////
static int statistics_negative_number_counter = 0;
static int statistics_zero_counter = 0;

static std::chrono::time_point<std::chrono::system_clock> debugging_time_end;

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

		camera_y_origin++;

		// Background circles
		circle_y_origin_change--;
	}
	if (user_input.down.is_down)
	{
		std::cout << "down" << std::endl;

		camera_y_origin--;

		// Backgroung circles
		//circle_y_origin_change++;
	}
	if (user_input.right.is_down)
	{
		std::cout << "right" << std::endl;

		camera_x_origin++;

		// Background circles
		// circle_x_origin_change--;
		//createCircle(camera_x_origin + akarin_width + 20, rand() % akarin_height);
	}
	if (user_input.left.is_down)
	{
		std::cout << "left" << std::endl;

		camera_x_origin--;

		// Background circles
		// circle_x_origin_change++;
		// createCircle(camera_x_origin - akarin_width + 20, rand() % akarin_height);
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
		if (!is_jumping)
		{
			ask_jump = true;
		}
	}
}

void createCircle(int position_x, int position_y)
{
	//std::cout << "creating circle" << std::endl;
	sf::CircleShape circle;
	circle.setRadius(10);

	circle.setPosition(
	    position_x,
	    position_y
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

void createAndRegisterAtom(int position_x, int position_y)
{
	Atom atom = Atom(rand() % 255, rand() % 255, rand() % 255, position_x, position_y);
	world_atom.push_back(atom);
};

void createCircleRandomly() {
	int circle_x_origin = (rand() % akarin_width) - radius;
	int circle_y_origin = (rand() % akarin_height) - radius;

	return createCircle(circle_x_origin, circle_y_origin);
}

void RenderAndUpdate(sf::RenderWindow *window, UserInput user_input)
{
	game_current_time = std::chrono::system_clock::now();
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

	for (int world_atom_iterator = 0; world_atom_iterator < circle_array.size(); world_atom_iterator++)
	{
		world_atom.at(world_atom_iterator).shape.setPosition(
		    camera_x_origin - world_atom.at(world_atom_iterator).position_x,
		    camera_y_origin - world_atom.at(world_atom_iterator).position_y
		);
		world->draw()
	}
	/**
		//createCircle();
		//draw the circlle
		for (int circle_array_iterator = 0; circle_array_iterator < circle_array.size(); circle_array_iterator++)
		{
			if (user_input.up.is_down)
			{
				circle_array.at(circle_array_iterator).move(0, 0);
			}
			if (user_input.down.is_down)
			{
				circle_array.at(circle_array_iterator).move(0, 0);
			}
			if (user_input.left.is_down)
			{
				circle_array.at(circle_array_iterator).move(2, 0);
			}
			if (user_input.right.is_down)
			{
				circle_array.at(circle_array_iterator).move(-2, 0);
			}

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
			window->draw(circle_array.at(circle_array_iterator));
		}
	**/
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
	character.setPosition(0 + camera_x_origin, akarin_height - (akarin_height / 9) - 100 + camera_y_origin);


	if (ask_jump)
	{
		// since the character is not jumping at the point of request, then this is essentially entry to jumping sequence
		if (!is_jumping)
		{
			// get the time when the jump was requested
			time_jump_start = game_current_time;

			// is_jumping prevents the player from requesting another jump while character is jumping
			is_jumping = true;

			std::cout << "beginning jumping sequece" << std::endl;
		}
		else
		{

			std::chrono::duration<double> elapsed_seconds = game_current_time - time_jump_start;
			if (elapsed_seconds.count() > 3.0f)
			{
				is_jumping = false;
				ask_jump = false;
				std::cout << "ending jumping sequece" << std::endl;
			} // if x < 1.5f, move up, else, move up
			else if (elapsed_seconds.count() < 1.5f)
			{
				camera_y_origin--;
			}
			else
			{
				camera_y_origin++;
			}
		}
	}

	window->draw(character);

	/**
	PERFORMANCE DEBUGGING

	-- Figure out how to print out fps, rendering time (ms), and other information
	**/
	debugging_time_end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = debugging_time_end - game_current_time;
	//std::cout << elapsed_seconds.count() << std::endl;
};
} //namespace Akarin