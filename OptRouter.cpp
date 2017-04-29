#include "OptRouter.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;


bool OptRouter::route() {
	cout << endl << endl;
	if (this->m_sourceIndex < 0 || this->m_targetIndex < 0 || this->m_row <= 0 || this->m_col <= 0) return false;
	this->m_path.clear();
	m_grids[this->m_sourceIndex] = 0;
	if (mazeSearch()) {
		mazeBacktrace();
		return true;
	}
	else return false;
}


const static int X[4] = { 1,0,-1,0 };
const static int Y[4] = { 0,1,0,-1 };

void OptRouter::mazeBacktrace() {

	int num = this->m_row * this->m_col;

	// f is the DP array
	int** f = new int*[num];
	for (int i = 0; i < num; i++) {
		f[i] = new int[4];
		for (int j = 0; j < 4; j++) f[i][j] = 99999999;
	}

	// Array from records the best answer
	pair<int, int>** from = new pair<int, int>*[num];
	for (int i = 0; i < num; i++)
		from[i] = new pair<int, int>[4];

	queue<pair<int, int> > Q;
	int x, y;
	for (int j = 0; j < 4; j++) {
		f[this->m_sourceIndex][j] = 0;
		from[this->m_sourceIndex][j] = make_pair(-1, -1);
		Q.push(make_pair(this->m_sourceIndex, j));
	}

	while (!Q.empty()) {
		pair<int, int> tmp = Q.front();
		int x0, y0, i0 = tmp.first, j0 = tmp.second, i, j;
		Q.pop();
		this->compXYIndex(i0, x0, y0);
		
		// turn right
		i = i0;
		j = (j0 == 0) ? 3 : j0 - 1;
		if (f[i][j] > f[i0][j0] + 1) {
			f[i][j] = f[i0][j0] + 1;
			from[i][j] = from[i0][j0];
			Q.push(make_pair(i, j));
		}

		// turn left
		i = i0;
		j = (j0 == 3) ? 0 : j0 + 1;
		if (f[i][j] > f[i0][j0] + 1) {
			f[i][j] = f[i0][j0] + 1;
			from[i][j] = from[i0][j0];
			Q.push(make_pair(i, j));
		}

		// go on in this direction
		int x = x0 + X[j0];
		int y = y0 + Y[j0];
		i = this->compIndex(x, y);
		j = j0;
		if (x >= 0 && x < this->m_col && y >= 0 && y < this->m_row) {
			if (this->m_grids[i] != -1 && this->m_grids[i0] + 1 == this->m_grids[i]) {
				if (f[i][j] > f[i0][j0]) {
					f[i][j] = f[i0][j0];
					from[i][j] = make_pair(i0, j0);
					Q.push(make_pair(i, j));
				}
			}
		}
	}

	int that, tmp = 99999999;
	for (int j=0;j<4;j++)
		if (f[this->m_targetIndex][j] < tmp) {
			tmp = f[this->m_targetIndex][j];
			that = j;
		}

	int i = this->m_targetIndex, j = that;
	while (i != -1) {
		this->m_path.push_back(i);
		pair<int, int> tmp = from[i][j];
		i = tmp.first;
		j = tmp.second;
	}


	printf("Found path: ");
	for (unsigned i = 0; i < this->m_path.size(); ++i) {
		int index = this->m_path[i];
		int x, y;
		this->compXYIndex(index, x, y);
		printf("[%d,%d] ", x, y);
	}
}