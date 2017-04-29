main.exe: main.o Board.o
	g++ main.o Board.o -o main.exe
main.o: main.cpp
	g++ -c main.cpp -o main.o
Board.o: Board.cpp
	g++ -c Board.cpp -o Board.o
clean:
	del *.o *.exe