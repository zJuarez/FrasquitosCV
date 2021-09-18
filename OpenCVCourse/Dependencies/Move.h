#ifndef Move_H
#define Move_H

#include "Color.h"
#include "Colores.h"
#include <vector>
#include <string>

#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
typedef std::vector<int> vi;

class Move {
private:
	int frascoOrigen;
	int frascoDestino;
	vi coordenadasFrascoOrigen;
	vi coordenadasFrascoDestino;
	Color color;
	bool valid;
	std::string coordenadasString(vi coordenadas);
public:
	Move(int frascoOrigen_, int frascoDestino_, vi coordenadasFrascoOrigen_,
		vi coordenadasFrascoDestino_, Color color_) {
		frascoOrigen = frascoOrigen_;
		frascoDestino = frascoDestino_;
		coordenadasFrascoOrigen = coordenadasFrascoOrigen_;
		coordenadasFrascoDestino = coordenadasFrascoDestino_;
		color = color_;
		valid = true;
	}
	int getFrascoOrigen();
	int getFrascoDestino();
	vi getCoordenadasFrascoOrigen();
	vi getCoordenadasFrascoDestino();
	bool getValid();
	Color getColor();
	Move(bool flag) { valid = false; }
	void print();
	void print(bool quitar);
	friend bool operator==(const Move& lhs, const Move& rhs) {
		return (lhs.frascoOrigen == rhs.frascoDestino &&
			lhs.coordenadasFrascoOrigen == rhs.coordenadasFrascoDestino &&
			lhs.color == rhs.color) ||
			(lhs.frascoOrigen == rhs.frascoOrigen &&
				lhs.frascoDestino == rhs.frascoDestino &&
				lhs.coordenadasFrascoOrigen == rhs.coordenadasFrascoOrigen &&
				lhs.coordenadasFrascoDestino == rhs.coordenadasFrascoDestino &&
				lhs.color == rhs.color);
	};
	std::string getPrintText();
};

#endif
