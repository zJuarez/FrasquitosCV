#ifndef ALGORITHM_V2_H
#define ALGORITHM_V2_H

#include "Color.h"
#include "Move.h"
#include "Imagen.h"
#include "AlgorithmUtils.h"
#include <map>
#include <unordered_map>

#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define trav(a, x) for (auto(a) : (x))
typedef std::vector<int> vi;

class AlgorithmV2
{
private:
	int trys;
	std::vector<std::vector<Imagen>> frasquitos;
	std::vector<Move> solution;
	std::map<Color, int> colorTopCountMap;
	void mover(Move move);
	void revertir(Move move);
public:
	AlgorithmV2(std::vector<std::vector<Imagen>> frasquitos_) {
		frasquitos = frasquitos_;
		trys = 0;
		trav(f, frasquitos)
			rep(i, 0, f.size())
			if (f[i].getColor() != Color::VACIO)
				colorTopCountMap[f[i].getColor()] += i + 1;

	};
	bool solve(std::vector<Move> moves);
	std::vector<Move> getSolution() { return solution; }

};

#endif