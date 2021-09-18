#include "AlgorithmV2.h"

// Comparator function to sort pairs
// according to second value
bool cmpMap(std::pair<Color, int>& a, std::pair<Color, int>& b) {
	return a.second < b.second;
}

// Function to sort the map according
// to value in a (key-value) pairs
std::vector<std::pair<Color, int>> sort(std::map<Color, int>& M) {

	// Declare vector of pairs
	std::vector<std::pair<Color, int>> A;

	// Copy key-value pair from Map
	// to vector of pairs
	for (auto& it : M) {
		A.push_back(it);
	}

	// Sort using comparator function
	std::sort(A.begin(), A.end(), cmpMap);

	return A;
}


void AlgorithmV2::mover(Move move) {

	int oldValue = 0;
	trav(posOrigen, move.getCoordenadasFrascoOrigen()) {
		frasquitos[move.getFrascoOrigen()][posOrigen].setColor(Color::VACIO);
		oldValue += posOrigen;
	}

	int newValue = 0;
	trav(posDestino, move.getCoordenadasFrascoDestino()) {
		frasquitos[move.getFrascoDestino()][posDestino].setColor(move.getColor());
		newValue += posDestino;
	}

	colorTopCountMap[move.getColor()] += (newValue - oldValue);
}

void AlgorithmV2::revertir(Move move) {

	int newValue = 0;
	trav(posOrigen, move.getCoordenadasFrascoOrigen()) {
		frasquitos[move.getFrascoOrigen()][posOrigen].setColor(move.getColor());
		newValue += posOrigen;
	}
	int oldValue = 0;
	trav(posDestino, move.getCoordenadasFrascoDestino()) {
		frasquitos[move.getFrascoDestino()][posDestino].setColor(Color::VACIO);
		oldValue += posDestino;
	}
	colorTopCountMap[move.getColor()] += (newValue - oldValue);
}

bool AlgorithmV2::solve(std::vector<Move> moves) {

	if (trys % 4000 == 0) {
		std::cout << " ITERATION: " << trys << std::endl;
		std::cout << " MOVES: " << moves.size() << std::endl;
		trav(move, moves) { move.print(); }
		AlgorithmUtils::print(frasquitos);
	}
	if (trys++ > AlgorithmUtils::MAX_TRYS)
		return false;

	if (AlgorithmUtils::win(frasquitos)) {
		std::cout << "=== WIN ===" << std::endl;
		std::cout << " ITERATION: " << trys << std::endl;
		std::cout << " MOVES: " << moves.size() << std::endl;
		trav(move, moves) { solution.pb(move); move.print(); }
		AlgorithmUtils::print(frasquitos);
		return true;
	}

	std::vector<std::pair<Color, int>> sortedMap = sort(colorTopCountMap);
	// print(frasquitos);

	trav(colorPair, sortedMap) {
		vi frascosWithColorOnTop =
			AlgorithmUtils::frasquitosWithColorOnTop(frasquitos, colorPair.first);
		trav(i, frascosWithColorOnTop) {
			rep(j, 0, frasquitos.size()) {
				if (i != j) {
					Move myMove = AlgorithmUtils::getMove(frasquitos, i, j);
					if (myMove.getValid() && (find(moves.begin(), moves.end(), myMove) == moves.end())) {
						moves.pb(myMove);
						mover(myMove);
						if (!solve(moves)) {
							revertir(myMove);
							moves.pop_back();
						}
						else {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
