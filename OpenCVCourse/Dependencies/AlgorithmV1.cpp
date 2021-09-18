#include "AlgorithmV1.h"

void AlgorithmV1::mover(Move move) {
	trav(posOrigen, move.getCoordenadasFrascoOrigen())
		frasquitos[move.getFrascoOrigen()][posOrigen].setColor(Color::VACIO);

	trav(posDestino, move.getCoordenadasFrascoDestino())
		frasquitos[move.getFrascoDestino()][posDestino].setColor(move.getColor());
}

void AlgorithmV1::revertir(Move move) {
	trav(posOrigen, move.getCoordenadasFrascoOrigen())
		frasquitos[move.getFrascoOrigen()][posOrigen].setColor(move.getColor());

	trav(posDestino, move.getCoordenadasFrascoDestino())
		frasquitos[move.getFrascoDestino()][posDestino].setColor(Color::VACIO);
}

bool AlgorithmV1::solve(std::vector<Move> moves) {

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
	// print(frasquitos);
	rep(in, 0, frasquitos.size()) {
		int i = (initial + in) % frasquitos.size();
		rep(jn, 0, frasquitos.size()) {
			int j = (initial + jn) % frasquitos.size();
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
	return false;
}

