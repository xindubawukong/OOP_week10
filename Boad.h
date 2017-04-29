

#ifndef Board_h
#define Board_h


#include <cstdlib>
#include <algorithm>
using namespace std;


class Point {
public:
	int x, y;
	Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
};


class Board {
private:
	pair<int, int> ***f;// f[i][j][k]
	pair<pair<int, int>, int> ***from;// record the best answer
	bool check(int x, int y); //check if Point(x,y) is valid
	bool update(pair<int, int> &a, int dist, int turn);// update a state
public:
	int M, N;// x in [0,M)   y in [0,N)
	Point S, T;// two terminals
	bool **can;// see if Point(x,y) is an obstacle
	Board(int _M, int _N);
	void setS(int x, int y);
	void setT(int x, int y);
	void setOpt(int x, int y);
	void dp();
	void output();
};


#endif