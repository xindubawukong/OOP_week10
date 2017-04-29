maze.exe: main.o maze.a OptRouter.o
	g++ main.o maze.a OptRouter.o -o maze.exe
main.o: main.cpp BaseRouter.h OptRouter.h
	g++ -c main.cpp -o main.o
OptRouter.o: OptRouter.cpp OptRouter.h
	g++ -c OptRouter.cpp -o OptRouter.o
clean:
	del *.exe *.o