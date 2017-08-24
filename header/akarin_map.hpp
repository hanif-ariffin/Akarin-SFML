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
public:
	std::string map_name;
	Map(int height, int width);
}
} //namespace Akarin