#if !defined(AKARIN_H)

#include <SFML/Graphics.hpp>

/*
The structure of buffer that will be displayed to our screen
*/
// macro for kilobytes,megabytes, gigabytes
#define Kilobytes(value) (value * 1024)
#define Megabytes(value) Kilobytes(value * 1024)
#define Gigabytes(value) Megabytes(value * 1024)

namespace Akarin {
struct Key {
	bool is_down;
	bool was_released;
};
struct UserInput
{
	Key up;
	Key down;
	Key left;
	Key right;
	Key space;
	Key q;
	Key w;
	Key e;
	Key r;
};

void RenderAndUpdate(
    sf::RenderWindow *window,
    UserInput user_input
);
}

#define AKARIN_H
#endif
