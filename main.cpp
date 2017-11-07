#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "engine.hpp"

#define DEFAULT_ICON "akarin_pic.png"
#define MATH_CONSTANT_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

int main()
{
	int width = 400;
	int height = 400;

	/*
	create the window
	you can only declare one of these
	*/
	sf::RenderWindow window(sf::VideoMode(width, height), "Akarin (SFML)");
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::Image icon;
	if (!icon.loadFromFile(DEFAULT_ICON))
	{
		std::cout << "Unable to load app icon" << std::endl;
	}
	else
	{
		std::cout << "Image successfully loaded" << std::endl;
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	/*
	Input struct
	*/
	Engine::UserInput user_input;
	/*
	Reset everything to false
	*/
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

	// run the program as long as the window is open
	while (window.isOpen())
	{
		/*
		Obtain the amount of time has passed since last rendering
		*/
		static SYSTEMTIME systemtime_time_begin_rendering = { 0 }, systemtime_time_end_rendering = { 0 }; // pointer to the current system time
		static Engine::TimePassed systemtime_time_between_rendering = { 0 }; //initialized to zero so the first rendation should process no physics
		GetSystemTime(&systemtime_time_begin_rendering);
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
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

				/**
				A beter implementation of 'holding' a key is to check if the key is released instead of using the repeated trigger that would be limited by the device
				**/
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "the escape key was pressed" << std::endl;
					std::cout << "control:" << event.key.control << std::endl;
					std::cout << "alt:" << event.key.alt << std::endl;
					std::cout << "shift:" << event.key.shift << std::endl;
					std::cout << "system:" << event.key.system << std::endl;
					window.close();
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					//std::cout << "left key pressed" << std::endl;
					user_input.left.is_down = true;
					//circle.move(-move_change_magnitude, 0);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					//std::cout << "right key pressed" << std::endl;
					user_input.right.is_down = true;
					//circle.move(move_change_magnitude, 0);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					//std::cout << "left key pressed" << std::endl;
					user_input.down.is_down = true;
					//circle.move(0, move_change_magnitude);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					//std::cout << "right key pressed" << std::endl;
					user_input.up.is_down = true;
					//circle.move(0, -move_change_magnitude);
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					//std::cout << "A key pressed" << std::endl;
					user_input.q.is_down = true;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.w.is_down = true;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::E)
				{
					//std::cout << "A key pressed" << std::endl;
					user_input.e.is_down = true;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.r.is_down = true;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.space.is_down = true;
					//circle.setPointCount(circle_sides_count);
				}
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Left)
				{
					//std::cout << "left key pressed" << std::endl;
					user_input.left.is_down = false;
					//circle.move(-move_change_magnitude, 0);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					//std::cout << "right key pressed" << std::endl;
					user_input.right.is_down = false;
					//circle.move(move_change_magnitude, 0);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					//std::cout << "left key pressed" << std::endl;
					user_input.down.is_down = false;
					//circle.move(0, move_change_magnitude);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					//std::cout << "right key pressed" << std::endl;
					user_input.up.is_down = false;
					//circle.move(0, -move_change_magnitude);
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					//std::cout << "A key pressed" << std::endl;
					user_input.q.is_down = false;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.w.is_down = false;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::E)
				{
					//std::cout << "A key pressed" << std::endl;
					user_input.e.is_down = false;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.r.is_down = false;
					//circle.setPointCount(circle_sides_count);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					//std::cout << "B key pressed" << std::endl;
					user_input.space.is_down = false;
					//circle.setPointCount(circle_sides_count);
				}
				break;
			}
		}
		// clear the window with black color
		//window.clear(sf::Color(0, 0, 0, 0));

		// Rendering here
		Engine::RenderAndUpdate(&window, &user_input, &systemtime_time_between_rendering);

		// Difference using SYSTEMTIME implementation
		GetSystemTime(&systemtime_time_end_rendering);
		systemtime_time_between_rendering.seconds = systemtime_time_end_rendering.wSecond - systemtime_time_begin_rendering.wSecond;
		systemtime_time_between_rendering.milliseconds = systemtime_time_end_rendering.wMilliseconds - systemtime_time_begin_rendering.wMilliseconds;

		/*
		Check for anomaly ( The seconds between rendering is 1 sec)
		then we skip this and provide akarin.cpp with (0 sec, 0 msec)).
		*/
		/*Output the contents given by the win32*/
		//std::cout << systemtime_time_between_rendering.seconds << " seconds " << systemtime_time_between_rendering.milliseconds << "mseconds" << std::endl;
		// end the current frame

		window.display();
	}

	return 0;
}
