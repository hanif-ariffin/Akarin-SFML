// SFML libraries
#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>
#include "engine.hpp"

namespace Engine
{

	// Global Variables
	static bool first_render = false;
	static int original_height = 0;
	static int original_width = 0;
	static int rgb_max_value = 254;
	static int rgb_min_value = 10;
	static std::vector<RectangleWithWeight> tail_array;
	//static int tail_lifetime = 10000;
	//static int tail_wait_counter = 0;

	// Variables for character
	static RectangleWithWeight character;
	static int character_x_origin = 0;
	static int character_y_origin = 0;

	// Variables for camera
	static int camera_x_origin = character_x_origin;
	static int camera_y_origin = character_y_origin;
	//static int camera_speed = 10;
	static int character_velocity_y = 0;
	static int character_velocity_x = 0;
	static int character_velocity_max = 150;

	// Variables for the background rendering
	static int background_red_color = 0;
	static bool background_red_color_going_up = true;
	static int background_green_color = 0;
	static bool background_green_color_going_up = true;
	static int background_blue_color = 0;
	static bool background_blue_color_going_up = true;
	static int background_alpha_value = 0;
	static bool background_alpha_value_going_up = true;

	void AddRectaglesToTail()
	{
		RectangleWithWeight rectangle;
		rectangle.rectangle.setSize(sf::Vector2f(character_velocity_max / 3, character_velocity_max / 3));
		rectangle.rectangle.setFillColor(sf::Color((rand() % 155), (rand() % 155), (rand() % 155)));
		rectangle.weight = 0;
		rectangle.position_x = character_x_origin;
		rectangle.position_y = character_y_origin;

		tail_array.push_back(rectangle);

	}

	void UpdateCharacterPosition()
	{
		character.position_x = character_x_origin;
		character.position_y = character_y_origin;
	};

	void UpdateCameraPosition()
	{
		camera_x_origin = character_x_origin;
		camera_y_origin = character_y_origin;
	};

	void ParseInput(UserInput *user_input)
	{
		if (user_input->up.is_down) /// UP
		{
			if (character_velocity_y < character_velocity_max) {
				character_velocity_y++;
			}
			character_y_origin += character_velocity_y;

			if (background_red_color_going_up)
			{
				background_red_color++;
			}
			else
			{
				background_red_color--;
			}
			if (background_red_color > rgb_max_value)
			{
				background_red_color_going_up = false;
			}
			else if (background_red_color < rgb_min_value)
			{
				background_red_color_going_up = true;
			}
		}
		else
		{
			if (character_velocity_y > 0)
			{
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

			if (background_green_color_going_up)
			{
				background_green_color++;
			}
			else
			{
				background_green_color--;
			}
			if (background_green_color > rgb_max_value)
			{
				background_green_color_going_up = false;
			}
			else if (background_green_color < rgb_min_value)
			{
				background_green_color_going_up = true;
			}
		}
		else
		{
			if (character_velocity_y < 0)
			{
				character_y_origin += character_velocity_y;
				character_velocity_y++;
			}
		}

		if (user_input->left.is_down) // LEFT
		{

			if (character_velocity_x > -character_velocity_max)
			{
				character_velocity_x--;
			}
			character_x_origin += character_velocity_x;

			if (background_alpha_value_going_up)
			{
				background_alpha_value++;
			}
			else
			{
				background_alpha_value--;
			}
			if (background_alpha_value > rgb_max_value)
			{
				background_alpha_value_going_up = false;
			}
			else if (background_alpha_value < rgb_min_value)
			{
				background_alpha_value_going_up = true;
			}
		}
		else
		{
			if (character_velocity_x < 0)
			{
				character_x_origin += character_velocity_x;
				character_velocity_x++;
			}
		}

		if (user_input->right.is_down) // RIGHT
		{
			if (character_velocity_x < character_velocity_max)
			{
				character_velocity_x++;
			}
			character_x_origin += character_velocity_x;

			if (background_blue_color_going_up)
			{
				background_blue_color++;
			}
			else
			{
				background_blue_color--;
			}
			if (background_blue_color > rgb_max_value)
			{
				background_blue_color_going_up = false;
			}
			else if (background_blue_color < rgb_min_value)
			{
				background_blue_color_going_up = true;
			}
		}
		else
		{
			if (character_velocity_x > 0)
			{
				character_x_origin += character_velocity_x;
				character_velocity_x--;
			}
		}
		if (user_input->q.is_down) // RIGHT
		{
			std::cout << "Q" << std::endl;
		}
		if (user_input->up.is_down || user_input->down.is_down || user_input->left.is_down || user_input->right.is_down)
		{
		};
	};

	void RenderAndUpdate(sf::RenderWindow* window, UserInput* user_input, TimePassed* given_time_passed)
	{
		// set the background color && clears it
		window->clear(sf::Color(
			background_red_color,
			background_green_color,
			background_blue_color,
			background_alpha_value
		));

		AddRectaglesToTail();

		// React to change in window size
		if ((original_width != window->getSize().x) || (original_height != window->getSize().y))
		{
			original_width = window->getSize().x;
			original_height = window->getSize().y;
			std::cout << "react accordingly to the change in screen size" << std::endl;
		}

		// Render relevent objects
		for (int tail_array_iterator = 0; tail_array_iterator < tail_array.size(); tail_array_iterator++)
		{
			// Additional check if the object is even within our camera's range
			if (tail_array.at(tail_array_iterator).rectangle.getSize().x == 0 && tail_array.at(tail_array_iterator).rectangle.getSize().y == 0)
			{
				//std::cout << "killed:" << tail_array.at(tail_array_iterator).position_x << " , " << tail_array.at(tail_array_iterator).position_x << " size:" << tail_array.size() << std::endl;
				tail_array.erase(tail_array.begin() + tail_array_iterator);
			}
			else
			{
				tail_array.at(tail_array_iterator).rectangle.setSize(sf::Vector2f(tail_array.at(tail_array_iterator).rectangle.getSize().x - 1, tail_array.at(tail_array_iterator).rectangle.getSize().y - 1));

				int screen_offset_x = tail_array.at(tail_array_iterator).position_x - camera_x_origin + (original_width / 2) - (tail_array.at(tail_array_iterator).rectangle.getSize().x / 2);
				int screen_offset_y = camera_y_origin - tail_array.at(tail_array_iterator).position_y + (original_height / 2) - (tail_array.at(tail_array_iterator).rectangle.getSize().y / 2);

#if DEBUGGING_CAMERA_RENDERING
				std::cout << offset_x << ", " << offset_y << " && "
					<< original_width << " , " << original_height << " && "
					<< tail_array.at(tail_array_iterator).position_x << ", " << camera_x_origin << " && "
					<< tail_array.at(tail_array_iterator).position_y << ", " << camera_y_origin << std::endl;
#endif
				tail_array.at(tail_array_iterator).rectangle.setPosition(screen_offset_x, screen_offset_y);
				window->draw(tail_array.at(tail_array_iterator).rectangle);
			}
		}

		//int old_camera_x_origin = camera_x_origin;
		//int old_camera_y_origin = camera_y_origin;
		ParseInput(user_input);

		// Update the camera position to follow the character
		UpdateCameraPosition();

		//Update character position
		UpdateCharacterPosition();

#if DEBUGGIND_CAMERA_RENDERING
		std::cout << (camera_x_origin - old_camera_x_origin) << ", " << (camera_y_origin - old_camera_y_origin) << std::endl;
#endif

		/*
		Should be removed and let character become the 'crosshair' instead
		*/
		sf::RectangleShape center;
		center.setSize(sf::Vector2f(character_velocity_max / 2, character_velocity_max / 2));
		center.setFillColor(sf::Color(255, 200, 255, 255));
		center.setPosition((original_width / 2) - (character_velocity_max / 2), (original_height / 2) - (character_velocity_max / 2));
		window->draw(center);


		//std::cout << "speed x:" << character_velocity_y << " y:" << character_velocity_x << std::endl;
	};
} //namespace Engine
