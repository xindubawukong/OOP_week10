#include <cstdio>
#include <iostream>
#include <queue>
#include <stack>
#include "Boad.h"
using namespace std;

#define inf 99999999


Board::Board(int _M, int _N) :M(_M), N(_N) {

	can = new bool*[M];
	for (int i = 0; i < M; i++) {
		can[i] = new bool[N];
		for (int j = 0; j < N; j++) can[i][j] = true;
	}

	f = new pair<int, int>**[M];
	for (int i = 0; i < M; i++) {
		f[i] = new pair<int, int>*[N];
		for (int j = 0; j < N; j++) {
			f[i][j] = new pair<int, int>[4];
			for (int k = 0; k < 4; k++)
				f[i][j][k] = make_pair(inf, inf);
		}
	}

	from = new pair<pair<int, int>, int>**[M];
	for (int i = 0; i < M; i++) {
		from[i] = new pair<pair<int, int>, int>*[N];
		for (int j = 0; j < N; j++)
			from[i][j] = new pair<pair<int, int>, int>[4];
	}
}


void Board::setS(int x, int y) {
	S = Point(x, y);
}
void Board::setT(int x, int y) {
	T = Point(x, y);
}
void Board::setOpt(int x, int y) {
	can[x][y] = false;
}


bool Board::update(pair<int, int> &a, int dist, int turn) {
	bool tmp = false;
	if (dist < a.first) {
		//if this path is shoter
		a = make_pair(dist, turn);
		tmp = true;
	}
	else if (dist == a.first && turn < a.second) {
		//if this path has the same length, but has less turns
		a.second = turn;
		tmp = true;
	}
	return tmp;
}
bool Board::check(int x, int y) {
	if (x < 0 || x >= M) return false;
	if (y < 0 || y >= N) return false;
	if (!can[x][y]) return false;
	return true;
}


void Board::dp() {

	bool ***inQueue = new bool**[M];
	for (int i = 0; i < M; i++) {
		inQueue[i] = new bool*[N];
		for (int j = 0; j < N; j++)
			inQueue[i][j] = new bool[4];
	}

	queue<pair<pair<int, int>, int> > Q;
	for (int k = 0; k < 4; k++) {
		// put the original states into the queue
		f[S.x][S.y][k] = make_pair(0, 0);
		Q.push(make_pair(make_pair(S.x, S.y), k));
		from[S.x][S.y][k] = make_pair(make_pair(-1, -1), -1);
	}

	// 0:down   1:right   2:up   3:left
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };

	while (!Q.empty()) {

		pair<pair<int, int>, int> tmp = Q.front();
		Q.pop();
		int x0 = tmp.first.first, y0 = tmp.first.second, k0 = tmp.second;
		inQueue[x0][y0][k0] = false;
		int dist = f[x0][y0][k0].first, turn = f[x0][y0][k0].second;
		int x, y, k;

		// turn left, and get a new state
		k = (k0 == 3) ? 0 : k0 + 1;
		x = x0;
		y = y0;
		if (update(f[x][y][k], dist, turn + 1)) {
			from[x][y][k] = from[x0][y0][k0];
			if (!inQueue[x][y][k]) {
				Q.push(make_pair(make_pair(x, y), k));
				inQueue[x][y][k] = true;
			}
		}

		// turn right, and get a new state
		k = (k0 == 0) ? 3 : k0 - 1;
		x = x0;
		y = y0;
		if (update(f[x][y][k], dist, turn + 1)) {
			from[x][y][k] = from[x0][y0][k0];
			if (!inQueue[x][y][k]) {
				Q.push(make_pair(make_pair(x, y), k));
				inQueue[x][y][k] = true;
			}
		}

		// go on a step in the current direction
		k = k0;
		x = x0 + dx[k];
		y = y0 + dy[k];
		if (check(x, y)) {
			if (update(f[x][y][k], dist + 1, turn)) {
				from[x][y][k] = make_pair(make_pair(x0, y0), k0);
				if (!inQueue[x][y][k]) {
					Q.push(make_pair(make_pair(x, y), k));
					inQueue[x][y][k] = true;
				}
			}
		}

	}
}


void Board::output() {
	/*
	// for debug using
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < 4; k++)
				cout << "f[" << i << ", " << j << ", " << k << "] = (" << f[i][j][k].first << ", " << f[i][j][k].second << ")" << endl;
	*/

	int t1 = inf, t2 = inf, k0;
	for (int k = 0; k < 4; k++) {
		if (f[T.x][T.y][k].first < t1) {
			t1 = f[T.x][T.y][k].first;
			t2 = f[T.x][T.y][k].second;
			k0 = k;
		}
		else if (f[T.x][T.y][k].first == t1 && f[T.x][T.y][k].second < t2) {
			t2 = f[T.x][T.y][k].second;
			k0 = k;
		}
	}
	stack<pair<pair<int, int>, int> > sta;
	int x0 = T.x, y0 = T.y;
	while (x0 != -1) {
		sta.push(make_pair(make_pair(x0, y0), k0));
		int x = from[x0][y0][k0].first.first;
		int y = from[x0][y0][k0].first.second;
		int k = from[x0][y0][k0].second;
		x0 = x, y0 = y, k0 = k;
	}
	cout << "The best path is:" << endl;
	while (!sta.empty()) {
		cout << " (" << sta.top().first.first << "," << sta.top().first.second << ") ";
		sta.pop();
	}
	cout << endl;
}
