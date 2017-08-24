#ifndef AKARIN_ATOM
#define AKARIN_ATOM

#include <SFML/Graphics.hpp>

namespace Akarin
{
class Atom
{
public:
	sf::RectangleShape shape;
	sf::Color color;

	Atom(sf::RectangleShape given_shape, sf::Color given_color);
	Atom(int red, int green, int blue);
};
} //namespace Akarin

#endif