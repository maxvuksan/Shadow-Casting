run: compile execute

compile:
	g++ -o main.exe -Isrc/include main.cpp Code/*.cpp -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

execute:
	./main.exe