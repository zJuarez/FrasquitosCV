#ifndef ALGORITHM_UTILS_H
#define ALGORITHM_UTILS_H

#include "Color.h"
#include "Move.h"
#include "Imagen.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>

#define pb push_back
#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define trav(a, x) for (auto(a) : (x))
typedef std::vector<int> vi;

namespace AlgorithmUtils
{
	const int COLORES_POR_FRASCO = 4;
	const int FRASCOS_VACIOS = 2;
	const int MAX_TRYS = 10000;
	void print(std::vector<std::vector<Imagen>> frasquitos);
	void initialSummary(std::vector<std::vector<Imagen>> frasquitos);
	bool win(std::vector<std::vector<Imagen>> frasquitos);
	Move getMove(std::vector<std::vector<Imagen>> frasquitos, int frascoOrigen, int frascoDestino);
	// v2 usage
	vi frasquitosWithColorOnTop(std::vector<std::vector<Imagen>> frasquitos, Color color);
};

#endif