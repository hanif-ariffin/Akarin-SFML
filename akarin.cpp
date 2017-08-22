#include "akarin.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

#define _USE_MATH_DEFINES // for C++  
#include <cmath>
/*
Our first try at rendering something to the display. This should get called at each instance of windowHandle
*/
namespace Akarin {
static void RenderAndUpdate(sf::RenderWindow window)
{
	int move_change_magnitude = 1;

	int radius = 40;
	int circle_sides_count = 20;

	sf::RenderWindow window(sf::VideoMode(height, width), "Akarin");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));

	// change the size to 100x100
	rectangle.setSize(sf::Vector2f(100, 100));

	// define a circle with radius = 200
	sf::CircleShape circle(radius);

	// change the radius to 40
	//circle.setRadius(40);
	circle.setPosition((height / 2 ) - (radius), (width / 2)  - (radius));

	// change the number of sides (points) to 100
	circle.setPointCount(circle_sides_count);

	window.draw(circle);
};
}