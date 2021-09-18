#include "AlgorithmUtils.h"

struct ColorAlgorithm {
	Color color;
	int pos;
	int quantity;

	ColorAlgorithm(Color color_, int pos_, int quantity_) {
		color = color_;
		pos = pos_;
		quantity = quantity_;
	}
};

int getConsecutiveColorQuantity(std::vector<Imagen> frasco, int pos) {
	int cont = 1;
	Color color = frasco[pos].getColor();
	rep(i, pos + 1, frasco.size()) {
		if (frasco[i].getColor() == color)
			cont++;
		else
			return cont;
	}
	return cont;
}

ColorAlgorithm getColorHastaArriba(std::vector<Imagen> frasco) {

	Color color = Color::VACIO;
	int quantity = 0;

	rep(i, 0, frasco.size()) {
		if (frasco[i].getColor() != Color::VACIO) {
			return ColorAlgorithm(frasco[i].getColor(), i, getConsecutiveColorQuantity(frasco, i));
		}
	}

	return ColorAlgorithm(Color::VACIO, frasco.size(), 0);
}

Move AlgorithmUtils::getMove(std::vector<std::vector<Imagen>> frasquitos, int frascoOrigen,
	int frascoDestino) {

	if (frasquitos[frascoDestino][0].getColor() != Color::VACIO)
		return Move(false);

	ColorAlgorithm colorHastaArribaOrigen = getColorHastaArriba(frasquitos[frascoOrigen]);

	if (colorHastaArribaOrigen.color == Color::VACIO)
		return Move(false);

	ColorAlgorithm colorHastaArribaDestino = getColorHastaArriba(frasquitos[frascoDestino]);

	if (colorHastaArribaDestino.color != colorHastaArribaOrigen.color &&
		colorHastaArribaDestino.color != Color::VACIO)
		return Move(false);

	// useless move
	if ((frasquitos[0].size() - colorHastaArribaOrigen.pos) == colorHastaArribaOrigen.quantity && colorHastaArribaDestino.color == Color::VACIO)
		return Move(false);

	int minQuantity = std::min(colorHastaArribaOrigen.quantity, colorHastaArribaDestino.pos);

	vi coordenadasFrascoOrigen;
	vi coordenadasFrascoDestino;

	rep(i, 0, minQuantity) {
		coordenadasFrascoOrigen.pb(colorHastaArribaOrigen.pos + i);
		coordenadasFrascoDestino.pb(colorHastaArribaDestino.pos - minQuantity + i);
	}

	return Move(frascoOrigen, frascoDestino, coordenadasFrascoOrigen, coordenadasFrascoDestino, colorHastaArribaOrigen.color);
}

bool AlgorithmUtils::win(std::vector<std::vector<Imagen>> frasquitos) {
	rep(i, 0, frasquitos.size()) {
		rep(j, 1, frasquitos[i].size()) {
			if (frasquitos[i][j].getColor() != frasquitos[i][0].getColor()) {
				return false;
			}
		}
	}
	return true;
}

void AlgorithmUtils::print(std::vector<std::vector<Imagen>> frasquitos) {
	int sizeFrasco = frasquitos[0].size();
	std::cout << std::endl;
	std::cout
		<< "   "
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   ";
	std::cout << std::endl;
	int mitad = frasquitos.size() / 2;
	bool impar = frasquitos.size() % 2 != 0;
	rep(i, 0, sizeFrasco) {
		rep(j, 0, impar ? mitad + 1 : mitad) std::cout
			<< std::setw(14) << colores[frasquitos[j][i].getColor()] << "    ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	rep(i, 0, sizeFrasco) {
		rep(j, impar ? mitad + 1 : mitad, frasquitos.size()) std::cout
			<< std::setw(14) << colores[frasquitos[j][i].getColor()] << "    ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout
		<< "   "
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   ";
	std::cout << std::endl;
}

void AlgorithmUtils::initialSummary(std::vector<std::vector<Imagen>> frasquitos) {
	std::unordered_map<Color, int> colorSummaryCount;

	trav(frasco, frasquitos)
		trav(liquido, frasco)
		colorSummaryCount[liquido.getColor()]++;

	std::cout << std::endl;
	std::cout
		<< "XXXXXXXXXXXXXXXXXXXXXXXXXXXX   SUMMARY    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	std::cout << std::endl;

	std::cout << std::setw(14) << "Frasquitos" << "  :  " << frasquitos.size() << std::endl;

	trav(color, colorSummaryCount)
		std::cout << std::setw(14) << colores[color.first] << "  :  " << color.second << std::endl;

	std::cout
		<< "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	std::cout << std::endl;
	std::cout << std::endl;

}

// v2 usage
vi AlgorithmUtils::frasquitosWithColorOnTop(std::vector<std::vector<Imagen>> frasquitos,
	Color color) {
	vi result;
	rep(i, 0, frasquitos.size()) {
		ColorAlgorithm colorHastaArriba = getColorHastaArriba(frasquitos[i]);
		if (colorHastaArriba.color == color)
			result.pb(i);
	}
	return result;
}

