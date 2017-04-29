#include <cstdio>
#include <iostream>
#include <algorithm>
#include "Boad.h"


int main() {
	Board* board = new Board(6, 6);
	board->setS(4, 1);
	board->setT(1, 4);

	board->setOpt(1, 1);
	board->setOpt(1, 3);
	board->setOpt(2, 1);
	board->setOpt(4, 4);

	board->dp();
	board->output();

	return 0;
}