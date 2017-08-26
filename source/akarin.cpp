// SFML libraries
#include <SFML/Graphics.hpp>

#include <stdlib.h>

#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

#include "../header/akarin.hpp"
#include "../header/akarin_math.hpp"

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
		shape.setSize(sf::Vector2f(50, 50));
		position_x = given_position_x;
		position_y = given_position_y;
	}
};

// Global Variables
static std::chrono::time_point<std::chrono::system_clock> game_current_time;
static bool initialized = false;
static int original_height = 0;
static int original_width = 0;

// World variables
std::vector<Atom *> world_atom;

// Variables for camera
static int camera_x_origin = 0;
static int camera_y_origin = 0;
static int camera_speed = 10;

// Variables for the character
static Atom actual_main_ship(0, 0, 0, 0, 0);
static Atom *main_ship = &actual_main_ship;
static int main_ship_speed_x = 10;
static int main_ship_speed_y = 10;

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
void UpdateCamera(UserInput *user_input)
{
	camera_x_origin = main_ship->position_x;
	camera_y_origin = main_ship->position_y;
}

void Shooting()
{
}

void Blink()
{

}

void SpawnBlocks(int amount)
{
	for (int iterator =  0; iterator < amount; iterator++)
	{
		world_atom.push_back(new Atom(
		                         (rand()  % 245) + 10,
		                         (rand() % 245) + 10,
		                         (rand() % 245) + 10,
		                         (camera_x_origin - (original_width / 2)) + (rand() % original_width),
		                         camera_y_origin + (original_width / 2) + 20
		                     ));
	}
}

void UpdateMainShip(UserInput *user_input)
{
	if (user_input->up.is_down) /// UP
	{
		main_ship->position_y += main_ship_speed_y;
	}
	if (user_input->down.is_down) // DOWN
	{
		main_ship->position_y -= main_ship_speed_y;
	}
	if (user_input->right.is_down) // RIGHT
	{
		main_ship->position_x += main_ship_speed_x;
	}
	if (user_input->left.is_down) // LEFT
	{
		main_ship->position_x -= main_ship_speed_x;
	}
	if (user_input->q.is_down) // Q
	{
		Shooting();
	}
	if (user_input->w.is_down) // W
	{
		Blink();
	}
	if (user_input->e.is_down) // E
	{
	}
	if (user_input->r.is_down) // R
	{
	}
	if (user_input->space.is_down) // SPACE
	{
	}
}

void createAndRegisterAtom(int position_x, int position_y)
{
	world_atom.push_back(new Atom(rand() % 255, rand() % 255, rand() % 255, position_x, position_y));
};

void createRectangleRandomly() {
	int circle_x_origin = camera_x_origin + (rand() % original_width);
	int circle_y_origin = camera_y_origin + (rand() % original_height);

	createAndRegisterAtom(circle_x_origin, circle_y_origin);
}

void RenderAndUpdate(sf::RenderWindow *window, UserInput *user_input)
{
	// Obtain the current game time
	game_current_time = std::chrono::system_clock::now();

	// Initialized variables
	if (!initialized)
	{
		original_width = window->getSize().x;
		original_height = window->getSize().y;
		main_ship->shape.setSize(sf::Vector2f(10, 30));
		world_atom.push_back(main_ship);

		initialized = true;
	}

	// React to change in window size
	if ((original_width != window->getSize().x) || (original_height != window->getSize().y))
	{
		std::cout << "react accordingly to the change in screen size" << std::endl;
	}

	// Is this really the way to do it?
	UpdateCamera(user_input);
	UpdateMainShip(user_input);
	SpawnBlocks(10);

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
		int offset_x = world_atom.at(world_atom_iterator)->position_x - camera_x_origin + (original_width / 2) - (world_atom.at(world_atom_iterator)->shape.getSize().x / 2);
		int offset_y = -(world_atom.at(world_atom_iterator)->position_y - camera_y_origin) + (original_height / 2) - (world_atom.at(world_atom_iterator)->shape.getSize().y / 2);
		if (world_atom_iterator > 1) { // not player's block
			offset_y -= 5;
		}
#if DEBUG
		std::cout << offset_x << ", " << offset_y <<  " from "
		          << world_atom.at(world_atom_iterator)->position_x << ", " << camera_x_origin << "&&"
		          << world_atom.at(world_atom_iterator)->position_y << ", " << camera_y_origin << std::endl;
#endif
		world_atom.at(world_atom_iterator)->shape.setPosition(offset_x, offset_y);
		window->draw(world_atom.at(world_atom_iterator)->shape);
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