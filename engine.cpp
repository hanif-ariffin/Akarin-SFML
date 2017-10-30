// SFML libraries
#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <iostream>

#include "engine.hpp"

namespace Engine
{

	// Global Variables
	static bool init = false;
	static int original_height = 0;
	static int original_width = 0;
	static int rgb_max_value = 254;
	static int rgb_min_value = 10;
	static std::vector<RectangleWithWeight> tail_array;
	static int tail_lifetime = 100000000;
	static int tail_wait_counter = 0;

	// Variables for camera movement
	static int camera_x_origin = 0;
	static int camera_y_origin = 0;
	static int camera_speed = 10;
	static int camera_acceleration_y = 0;
	static int camera_acceleration_x = 0;
	static int camera_acceleration_max = 1;

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
		RectangleWithWeight tuple;
		tuple.rectangle.setSize(sf::Vector2f(8, 8));
		tuple.rectangle.setFillColor(sf::Color((rand() % 155), (rand() % 155), (rand() % 155)));
		tuple.weight = 0;
		tuple.position_x = camera_x_origin;
		tuple.position_y = camera_y_origin;

		tail_array.push_back(tuple);

	}
	void ParseInput(UserInput *user_input)
	{
		if (user_input->up.is_down) /// UP
		{
			if (camera_acceleration_y < camera_acceleration_max) {
				camera_acceleration_y++;
			}
			camera_y_origin += camera_acceleration_y;

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
			if (camera_acceleration_y != 0)
			{
				camera_acceleration_y--;
				camera_y_origin += camera_acceleration_y;
			}
		}

		if (user_input->down.is_down) // DOWN
		{
			if (camera_acceleration_y > -camera_acceleration_max) {
				camera_acceleration_y--;
			}
			camera_y_origin += camera_acceleration_y;

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
			if (camera_acceleration_y != 0)
			{
				camera_acceleration_y++;
				camera_y_origin += camera_acceleration_y;
			}
		}

		if (user_input->left.is_down) // LEFT
		{

			if (camera_acceleration_x > -camera_acceleration_max)
			{
				camera_acceleration_x--;
			}
			camera_x_origin += camera_acceleration_x;

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
			if (camera_acceleration_x != 0)
			{
				camera_acceleration_x++;
				camera_x_origin += camera_acceleration_x;
			}
		}

		if (user_input->right.is_down) // RIGHT
		{
			if (camera_acceleration_x < camera_acceleration_max)
			{
				camera_acceleration_x++;
			}
			camera_x_origin += camera_acceleration_x;

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
			if (camera_acceleration_x != 0)
			{
				camera_acceleration_x--;
				camera_x_origin += camera_acceleration_x;
			}
		}
		if (user_input->q.is_down) // RIGHT
		{
			std::cout << "Q" << std::endl;
		}
		if (user_input->up.is_down || user_input->down.is_down || user_input->left.is_down || user_input->right.is_down)
		{
			if ((tail_wait_counter++ % 1) == 0)
			{
			}
		};
	};

	void RenderAndUpdate(sf::RenderWindow * window, UserInput * user_input)
	{
		// set the background color
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

		for (int tail_array_iterator = 0; tail_array_iterator < tail_array.size(); tail_array_iterator++)
		{
			if (tail_array.at(tail_array_iterator).weight++ == tail_lifetime)
			{
				std::cout << "killed:" << tail_array.at(tail_array_iterator).position_x << " , " << tail_array.at(tail_array_iterator).position_x << std::endl;
				tail_array.erase(tail_array.begin() + tail_array_iterator);
			}
			else
			{
				int offset_x = tail_array.at(tail_array_iterator).position_x - camera_x_origin + (original_width / 2) - (tail_array.at(tail_array_iterator).rectangle.getSize().x / 2);
				int offset_y = camera_y_origin - tail_array.at(tail_array_iterator).position_y + (original_height / 2) - (tail_array.at(tail_array_iterator).rectangle.getSize().y / 2);

#if DEBUGGING_CAMERA_RENDERING
				std::cout << offset_x << ", " << offset_y << " && "
					<< original_width << " , " << original_height << " && "
					<< tail_array.at(tail_array_iterator).position_x << ", " << camera_x_origin << " && "
					<< tail_array.at(tail_array_iterator).position_y << ", " << camera_y_origin << std::endl;
#endif
				tail_array.at(tail_array_iterator).rectangle.setPosition(offset_x, offset_y);
				window->draw(tail_array.at(tail_array_iterator).rectangle);
			}
		}
		int old_camera_x_origin = camera_x_origin;
		int old_camera_y_origin = camera_y_origin;
		ParseInput(user_input);
#if DEBUGGIND_CAMERA_RENDERING
		std::cout << (camera_x_origin - old_camera_x_origin) << ", " << (camera_y_origin - old_camera_y_origin) << std::endl;
#endif
		sf::RectangleShape center;
		int size_x = 10;
		int size_y = 10;
		center.setSize(sf::Vector2f(size_x, size_y));
		center.setFillColor(sf::Color(255, 200, 255, 255));
		center.setPosition((original_width / 2) - (size_x / 2), (original_height / 2) - (size_y / 2));
		window->draw(center);
	};
} //namespace Engine
