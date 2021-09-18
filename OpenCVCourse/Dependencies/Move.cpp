#include "Move.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << " [";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "] ";
	return os;
}

std::string Move::coordenadasString(vi x) {
	std::string ret = " [";
	rep(i, 0, x.size()) {
		ret += std::to_string(x[i]);
		if (i != x.size() - 1)
			ret += ",";
	}
	ret += "] ";
	return ret;
}
std::string Move::getPrintText() {
	std::string ret = " de frasquito " +
		std::to_string(frascoOrigen + 1) +
		coordenadasString(coordenadasFrascoOrigen) +
		"a frasquito " + std::to_string(frascoDestino + 1) +
		coordenadasString(coordenadasFrascoDestino);
	return ret;
}
void Move::print() {
	std::cout << std::endl;
	std::cout << colores[color] << " de frasquito " << frascoOrigen + 1
		<< coordenadasFrascoOrigen << "a frasquito " << frascoDestino + 1
		<< coordenadasFrascoDestino << std::endl;
};
void Move::print(bool quitar) {
	std::cout << "QUITAR: ";
	print();
};

int Move::getFrascoOrigen() {
	return frascoOrigen;
}
int Move::getFrascoDestino() {
	return frascoDestino;
}
vi Move::getCoordenadasFrascoOrigen() {
	return coordenadasFrascoOrigen;
}
vi Move::getCoordenadasFrascoDestino() {
	return coordenadasFrascoDestino;
}
bool Move::getValid() {
	return valid;
}
Color Move::getColor() {
	return color;
}