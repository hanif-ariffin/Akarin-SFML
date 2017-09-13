echo "begin buiding"
if [ ! -d "obj" ]; then
	mkdir obj
fi
rm -rf obj/*
if [ ! -d "bin" ]; then
	mkdir bin
fi
rm -rf bin/*
if ! dpkg -s libsfml-dev  > /dev/null; then
	echo -e "SFML not found! Install? (y/n) \c"
	read
	if "$REPLY" = "y"; then
		sudo apt-get install libsfml-dev
	fi
else
	echo "SFML is installed"
fi
g++ -c main.cpp -o obj/main.o
g++ -c engine.cpp -o obj/engine.o

g++ obj/main.o obj/engine.o -o bin/game -lsfml-graphics -lsfml-window -lsfml-system

echo "clean up obj files"
rm -rf obj
