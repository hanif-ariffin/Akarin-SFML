#if !defined(AKARIN_H)
/*
The structure of buffer that will be displayed to our screen
*/
// macro for kilobytes,megabytes, gigabytes
#define Kilobytes(value) (value * 1024)
#define Megabytes(value) Kilobytes(value * 1024)
#define Gigabytes(value) Megabytes(value * 1024)

namespace Akarin {
struct GameInput
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool space;
};

static void RenderAndUpdateGame(
    sf::RenderWindow window,
    GameInput game_input
);
}

#define AKARIN_H
#endif