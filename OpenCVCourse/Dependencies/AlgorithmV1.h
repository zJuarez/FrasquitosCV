#ifndef ALGORITHM_V1_H
#define ALGORITHM_V1_H

#include "Color.h"
#include "Move.h"
#include "Imagen.h"
#include "AlgorithmUtils.h"
#include <iostream>

#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define trav(a, x) for (auto(a) : (x))
typedef std::vector<int> vi;

class AlgorithmV1
{
private:
	int trys;
	int initial;
	std::vector<std::vector<Imagen>> frasquitos;
	std::vector<Move> solution;
	void mover(Move move);
	void revertir(Move move);

public:
	AlgorithmV1(std::vector<std::vector<Imagen>> frasquitos_, int initial_ = 0) {
		frasquitos = frasquitos_;
		initial = initial_;
		trys = 0;
	};
	bool solve(std::vector<Move> moves);
	std::vector<Move> getSolution() { return solution; }

};

#endif