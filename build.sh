echo "begin buiding"
if [ ! -d "obj" ]; then
	mkdir obj
fi
rm -rf obj/*
if [ ! -d "bin" ]; then
	mkdir bin
fi
rm -rf bin/*

g++ -c main.cpp -o obj/main.o
g++ -c engine.cpp -o obj/engine.o

g++ obj/main.o obj/engine.o -o bin/game -lsfml-graphics -lsfml-window -lsfml-system

echo "clean up obj files"
rm -rf obj
