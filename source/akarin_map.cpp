#include <stdlib.h>
#include <string>

#include "akarin_atom.hpp"

/*
Map class will define every object's coordinate on the map
*/
namespace Akarin
{
class Map
{
private:
	std::vector<std::vector<Akarin::Atom> > map;
	int height;
	int width;
public:
	std::string map_name;
	Map(int given_height, given_width)
	{
		height = given_height;
		width = given_width;
	}
}
} //namespace Akarin