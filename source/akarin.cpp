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
		shape.setSize(sf::Vector2f(5, 5));
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
static bool initialized = false;
static int original_height = 0;
static int original_width = 0;

// World variables
std::vector<Atom> world_atom;
static int explored_map_x_right = 0;
static int explored_map_x_left = 0;
static int explored_map_y_up = 0;
static int explored_map_y_down = 0;

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
static int camera_speed = 10;
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

// Variables for debugging purposes
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
	if (user_input.up.is_down) /// UP
	{
		std::cout << "up" << std::endl;

		explored_map_y_up += camera_speed;
		camera_y_origin += camera_speed;

		// Background circles
		//circle_y_origin_change--;
	}
	if (user_input.down.is_down) // DOWN
	{
		std::cout << "down" << std::endl;

		explored_map_y_down += camera_speed;
		camera_y_origin -= camera_speed;

		// Backgroung circles
		//circle_y_origin_change++;
	}
	if (user_input.right.is_down) // RIGHT
	{
		std::cout << "right" << std::endl;

		explored_map_x_right += camera_speed;
		camera_x_origin += camera_speed;

		// Background circles
		// circle_x_origin_change--;
		//createCircle(camera_x_origin + original_width + 20, rand() % original_height);
	}
	if (user_input.left.is_down) // LEFT
	{
		std::cout << "left" << std::endl;

		explored_map_x_left += camera_speed;
		camera_x_origin -= camera_speed;

		// Background circles
		// circle_x_origin_change++;
		// createCircle(camera_x_origin - original_width + 20, rand() % original_height);
	}
	if (user_input.q.is_down) // Q
	{
		std::cout << "q" << std::endl;
		background_red_color++;
	}
	if (user_input.w.is_down) // W
	{
		std::cout << "w" << std::endl;
		background_green_color++;
	}
	if (user_input.e.is_down) // E
	{
		std::cout << "e" << std::endl;
		background_blue_color++;
	}
	if (user_input.r.is_down) // R
	{
		std::cout << "r" << std::endl;
		background_alpha_value++;
	}
	if (user_input.space.is_down) // SPACE
	{
		std::cout << "space" << std::endl;
		createAndRegisterAtom(camera_x_origin, -camera_y_origin);
	}
}

void createAndRegisterAtom(int position_x, int position_y)
{
	world_atom.push_back(Atom(rand() % 255, rand() % 255, rand() % 255, position_x, position_y));
};

void createRectangleRandomly() {
	int circle_x_origin = camera_x_origin + (rand() % original_width);
	int circle_y_origin = camera_y_origin + (rand() % original_height);

	createAndRegisterAtom(circle_x_origin, circle_y_origin);
}

void RenderAndUpdate(sf::RenderWindow *window, UserInput user_input)
{
	// Obtain the current game time
	game_current_time = std::chrono::system_clock::now();

	//std::cout << rand_with_negative(rand()) << ", " << rand_with_negative_2(rand()) << std::endl;
	//std::cout << RAND_MAX << std::endl;
	//std::cout << window->getSize().x << ", " << window->getSize().y << std::endl;
	//std::cout << "random:" << (rand() % original_height) << ", " << (rand() % original_width) << std::endl;

	// obtain the width and height from window
	if (!initialized)
	{
		original_width = window->getSize().x;
		original_height = window->getSize().y;
		world_atom.push_back(Atom(0, 0, 0, 0, 0));

		explored_map_x_right = original_width / 2;
		explored_map_x_left = original_width / 2;
		explored_map_y_up = original_height  / 2;
		explored_map_y_down = original_height / 2;


		initialized = true;
	}

	if ((original_width != window->getSize().x) || (original_height != window->getSize().y))
	{
		std::cout << "react accordingly to the change in screen size" << std::endl;
	}

	ParseUserInput(user_input);

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
	/**
	sf::RectangleShape ground;
	ground.setSize(sf::Vector2f(original_width, (original_height / 9)));
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(0, original_height - (original_height / 9));
	window->draw(ground);
	**/
	/**
	// Render the character
	sf::RectangleShape character;
	character.setSize(sf::Vector2f(30, 100));
	character.setFillColor(sf::Color::Black);
	character.setPosition(0 + camera_x_origin, original_height - (original_height / 9) - 100 + camera_y_origin);

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
	**/

	/*
	At this point we should be done with everything and just have to draw into the window
	*/

	// set the background color
	window->clear(sf::Color(
	                  background_red_color,
	                  background_green_color,
	                  background_blue_color,
	                  background_alpha_value
	              ));

	// draw every object on the window
	for (int world_atom_iterator = 0; world_atom_iterator < world_atom.size(); world_atom_iterator++)
	{
		world_atom.at(world_atom_iterator).shape.setPosition(
		    world_atom.at(world_atom_iterator).position_x - camera_x_origin + (original_width / 2) - (world_atom.at(world_atom_iterator).shape.getSize().x / 2),
		    world_atom.at(world_atom_iterator).position_y + camera_y_origin + (original_height / 2) - (world_atom.at(world_atom_iterator).shape.getSize().y / 2)
		);
		window->draw(world_atom.at(world_atom_iterator).shape);
	}

	/**
	PERFORMANCE DEBUGGING

	-- Figure out how to print out fps, rendering time (ms), and other information
	**/
	debugging_time_end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = debugging_time_end - game_current_time;
	//std::cout << elapsed_seconds.count() << std::endl;
};
} //namespace Akarin