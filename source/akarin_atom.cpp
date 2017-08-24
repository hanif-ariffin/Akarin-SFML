#include <SFML/Graphics.hpp>

namespace Akarin
{
class Atom
{
public:
	sf::RectangleShape shape;
	sf::Color color;

	Atom(sf::RectangleShape given_shape, sf::Color given_color)
	{
		shape = given_shape;
		color = given_color;
	}

	Atom(int red, int green, int blue)
	{
		shape = new sf::RectangleShape(2);
		color = new sf::Color(red, green, blue);
	}
};
} //namespace Akarin
