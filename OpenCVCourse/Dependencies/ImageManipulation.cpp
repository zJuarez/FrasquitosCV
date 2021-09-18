#include "ImageManipulation.h"

bool ImageManipulation::imageComparator(Imagen& a, Imagen& b) {

	int range = 10;
	// same floor (returns minor x)
	if (a.getPoint().y > b.getPoint().y - range &&
		a.getPoint().y < b.getPoint().y + range) {
		return a.getPoint().x < b.getPoint().x;
	}
	// a is first floor b is second floor
	return a.getPoint().y + range < b.getPoint().y;
}

std::vector<Color> getColoresFrasco(Imagen frasco, std::vector<Imagen> liquidos) {
	std::vector<Color> coloresFrasco;
	std::vector<Imagen> liquidosFrasco;
	trav(liquido, liquidos)
		if (frasco.getRect().contains(liquido.getPoint()))
			liquidosFrasco.push_back(liquido);

	sort(liquidosFrasco.begin(), liquidosFrasco.end(), ImageManipulation::imageComparator);

	for (int i = 0; i < liquidosFrasco.size() && i < AlgorithmUtils::COLORES_POR_FRASCO; i++)
		coloresFrasco.push_back(liquidosFrasco[i].getColor());

	int sizeColores = coloresFrasco.size();

	if (sizeColores == 0) {

		std::vector<Color> vacio(AlgorithmUtils::COLORES_POR_FRASCO, Color::VACIO);
		return vacio;
	}
	else if (sizeColores == 1) {

		std::vector<Color> singleColor(AlgorithmUtils::COLORES_POR_FRASCO, coloresFrasco[0]);
		return singleColor;
	}
	else if (sizeColores == 2) {

		int greatestHeight =
			liquidosFrasco[0].getRect().height < liquidosFrasco[1].getRect().height;
		int smallestHeight = greatestHeight == 1 ? 0 : 1;
		int factor = round((double)liquidosFrasco[greatestHeight].getRect().height /
			(double)liquidosFrasco[smallestHeight].getRect().height);
		std::vector<Color> biggestHeightColor(factor == 1 ? AlgorithmUtils::COLORES_POR_FRASCO / 2
			: AlgorithmUtils::COLORES_POR_FRASCO - 1,
			coloresFrasco[greatestHeight]);
		std::vector<Color> smallestHeightColor(factor == 1 ? AlgorithmUtils::COLORES_POR_FRASCO / 2
			: 1,
			coloresFrasco[smallestHeight]);

		if (smallestHeight) {
			std::vector<Color> twoColors(biggestHeightColor);
			twoColors.insert(twoColors.end(), smallestHeightColor.begin(),
				smallestHeightColor.end());
			return twoColors;
		}
		else {
			std::vector<Color> twoColors(smallestHeightColor);
			twoColors.insert(twoColors.end(), biggestHeightColor.begin(),
				biggestHeightColor.end());
			return twoColors;
		}

	}
	else if (sizeColores == AlgorithmUtils::COLORES_POR_FRASCO - 1) {
		int maxHeightIndex = 0;
		int maxHeight = 0;
		std::vector<Color> multipleColors;
		rep(i, 0, liquidosFrasco.size()) {
			if (liquidosFrasco[i].getRect().height > maxHeight) {
				maxHeightIndex = i;
				maxHeight = liquidosFrasco[i].getRect().height;
			}
		}
		rep(i, 0, liquidosFrasco.size()) {
			multipleColors.push_back(liquidosFrasco[i].getColor());
			if (maxHeightIndex == i) {
				multipleColors.push_back(liquidosFrasco[i].getColor());
			}
		}
		return multipleColors;
	}

	return coloresFrasco;
}
std::vector<std::vector<Color>> getColorMatrixFromLiquidosAndFrascos(std::vector<Imagen> frascos,
	std::vector<Imagen> liquidos) {

	std::vector<std::vector<Color>> result;

	sort(frascos.begin(), frascos.end(), ImageManipulation::imageComparator);

	trav(frasco, frascos)
		result.push_back(getColoresFrasco(frasco, liquidos));

	return result;
}

std::pair <cv::Mat, std::vector<std::vector<Imagen>>> ImageManipulation::getInitialImageAndMatrix(std::vector<std::vector<Color>> frasquitos) {

	int mitad = frasquitos.size() / 2;
	bool impar = frasquitos.size() % 2 != 0;
	int nFrascosPorNivel = impar ? mitad + 1 : mitad;
	cv::Mat background(
		cv::Size(nFrascosPorNivel * ImageManipulation::frascoWidth + (nFrascosPorNivel + 1) * ImageManipulation::marginX,
			ImageManipulation::marginY + ImageManipulation::marginY / 2 + ImageManipulation::marginYMid + 2 * ImageManipulation::frascoHeight),
		CV_8UC3, cv::Scalar(0, 0, 0));

	std::vector<Imagen> frasquito(AlgorithmUtils::COLORES_POR_FRASCO);

	std::vector<std::vector<Imagen>> frasquitosOut(frasquitos.size(), frasquito);
	int width = ImageManipulation::marginX;
	int height = ImageManipulation::marginY;
	rep(i, 0, nFrascosPorNivel) {
		rectangle(background, cv::Point2i(width, height),
			cv::Point2i(width + ImageManipulation::frascoWidth, height + ImageManipulation::frascoHeight),
			ImageManipulation::getColorRGBScalar(Color::FRASCO), ImageManipulation::frascoContainerThickness);
		height += ImageManipulation::topEmptyFrascoHeight;
		rep(j, 0, frasquitos[i].size()) {
			cv::Point2i topLeftPoint = cv::Point2i(width + ImageManipulation::frascoContainerThickness, height);
			cv::Point2i bottomRightPoint =
				cv::Point2i(width + ImageManipulation::liquidoWidth + ImageManipulation::frascoContainerThickness,
					height + ImageManipulation::liquidoHeight);
			frasquitosOut[i][j] =
				Imagen(frasquitos[i][j], cv::Rect(topLeftPoint, bottomRightPoint),
					width + ImageManipulation::liquidoWidth / 2 + ImageManipulation::frascoContainerThickness,
					height + ImageManipulation::liquidoHeight / 2);
			rectangle(background, topLeftPoint, bottomRightPoint,
				ImageManipulation::getColorRGBScalar(frasquitos[i][j]), cv::FILLED);
			height += ImageManipulation::liquidoHeight;
		}
		height = ImageManipulation::marginY;
		width += ImageManipulation::frascoWidth + ImageManipulation::marginX;
	}

	height = ImageManipulation::marginY + ImageManipulation::frascoHeight + ImageManipulation::marginYMid;
	width = ImageManipulation::marginX;

	rep(i, impar ? mitad + 1 : mitad, frasquitos.size()) {
		rectangle(background, cv::Point2i(width, height),
			cv::Point2i(width + ImageManipulation::frascoWidth, height + ImageManipulation::frascoHeight),
			ImageManipulation::getColorRGBScalar(Color::FRASCO), ImageManipulation::frascoContainerThickness);
		height += ImageManipulation::topEmptyFrascoHeight;
		rep(j, 0, frasquitos[i].size()) {
			cv::Point2i topLeftPoint = cv::Point2i(width + ImageManipulation::frascoContainerThickness, height);
			cv::Point2i bottomRightPoint =
				cv::Point2i(width + ImageManipulation::liquidoWidth + ImageManipulation::frascoContainerThickness,
					height + ImageManipulation::liquidoHeight);
			frasquitosOut[i][j] =
				Imagen(frasquitos[i][j], cv::Rect(topLeftPoint, bottomRightPoint),
					width + ImageManipulation::liquidoWidth / 2 + ImageManipulation::frascoContainerThickness,
					height + ImageManipulation::liquidoHeight / 2);
			rectangle(background, topLeftPoint, bottomRightPoint,
				ImageManipulation::getColorRGBScalar(frasquitos[i][j]), cv::FILLED);
			height += ImageManipulation::liquidoHeight;
		}
		height = ImageManipulation::marginY + ImageManipulation::frascoHeight + ImageManipulation::marginYMid;
		width += ImageManipulation::frascoWidth + ImageManipulation::marginX;
	}

	return mp(background, frasquitosOut);
}


cv::Scalar ImageManipulation::getColorRGBScalar(Color color) {
	switch (color) {
	case CAFE:
		return CV_RGB(125, 74, 8);
	case AZUL:
		return CV_RGB(59, 47, 195);
	case VERDE_CESPED:
		return CV_RGB(120, 151, 14);
	case ROSA:
		return CV_RGB(234, 94, 123);
	case MORADO:
		return CV_RGB(114, 43, 147);
	case VERDE_FOSFO:
		return CV_RGB(97, 214, 125);
	case CELESTE:
		return CV_RGB(85, 163, 227);
	case GRIS:
		return CV_RGB(99, 100, 102);
	case VERDE_FUERTE:
		return CV_RGB(17, 101, 51);
	case NARANJA:
		return CV_RGB(232, 140, 65);
	case ROJO:
		return CV_RGB(196, 43, 35);
	case AMARILLO:
		return CV_RGB(241, 218, 88);
	case FRASCO:
		return CV_RGB(125, 125, 125);
	case VACIO:
		return CV_RGB(35, 35, 35);
	default:
		return CV_RGB(0, 0, 0);
	}
}
std::pair <cv::Mat, std::vector<std::vector<Imagen>>> ImageManipulation::getInitialImageAndMatrix(std::vector<Imagen> frascos, std::vector<Imagen> liquidos) {

	std::vector<std::vector<Color>> matColores =
		getColorMatrixFromLiquidosAndFrascos(frascos, liquidos);
	return getInitialImageAndMatrix(matColores);

}

std::vector<cv::Mat> ImageManipulation::getSolutionImages(std::vector<Move> moves, std::vector<std::vector<Imagen>> frasquitos, cv::Mat img) {
	std::vector<cv::Mat> images;
	images.push_back(img.clone());
	trav(move, moves) {
		trav(posOrigen, move.getCoordenadasFrascoOrigen()) {
			rectangle(img, frasquitos[move.getFrascoOrigen()][posOrigen].getRect(), ImageManipulation::getColorRGBScalar(Color::VACIO), cv::FILLED);
			frasquitos[move.getFrascoOrigen()][posOrigen].setColor(Color::VACIO);
		}
		trav(posDestino, move.getCoordenadasFrascoDestino()) {
			rectangle(img, frasquitos[move.getFrascoDestino()][posDestino].getRect(), ImageManipulation::getColorRGBScalar(move.getColor()), cv::FILLED);
			frasquitos[move.getFrascoDestino()][posDestino].setColor(move.getColor());
		}
		images.push_back(img.clone());
	}
	return images;
}


cv::Mat ImageManipulation::putInstructionsOnImage(std::vector<std::vector<Imagen>> frasquitos,
	Move move, cv::Mat img) {

	circle(img, cv::Point(60, 75), 15, ImageManipulation::getColorRGBScalar(move.getColor()), cv::FILLED);
	putText(img, move.getPrintText(), cv::Point(90, 80), 0, 0.8, CV_RGB(255, 255, 255));

	trav(posOrigen, move.getCoordenadasFrascoOrigen()) {
		rectangle(img, frasquitos[move.getFrascoOrigen()][posOrigen].getRect(),
			CV_RGB(255, 255, 255), cv::FILLED);
		cv::Mat roi = img(frasquitos[move.getFrascoOrigen()][posOrigen].getRect());
		cv::Mat color(roi.size(), CV_8UC3, ImageManipulation::getColorRGBScalar(move.getColor()));
		double alpha = 0.5;
		cv::addWeighted(color, alpha, roi, 1.0 - alpha, 0.0, roi);
		rectangle(img, frasquitos[move.getFrascoOrigen()][posOrigen].getRect(),
			CV_RGB(255, 255, 255), 2);
	}

	trav(posDestino, move.getCoordenadasFrascoDestino()) {
		rectangle(img, frasquitos[move.getFrascoDestino()][posDestino].getRect(),
			CV_RGB(255, 255, 255), 2);
	}

	rectangle(img,
		cv::Point2i(frasquitos[move.getFrascoOrigen()][0].getRect().tl().x -
			frascoContainerThickness,
			frasquitos[move.getFrascoOrigen()][0].getRect().tl().y -
			topEmptyFrascoHeight),
		cv::Point2i(frasquitos[move.getFrascoOrigen()][0].getRect().tl().x -
			frascoContainerThickness + frascoWidth,
			frasquitos[move.getFrascoOrigen()][0].getRect().tl().y -
			topEmptyFrascoHeight + frascoHeight),
		CV_RGB(255, 255, 255), 2);

	rectangle(img,
		cv::Point2i(frasquitos[move.getFrascoDestino()][0].getRect().tl().x -
			frascoContainerThickness,
			frasquitos[move.getFrascoDestino()][0].getRect().tl().y -
			topEmptyFrascoHeight),
		cv::Point2i(frasquitos[move.getFrascoDestino()][0].getRect().tl().x -
			frascoContainerThickness + frascoWidth,
			frasquitos[move.getFrascoDestino()][0].getRect().tl().y -
			topEmptyFrascoHeight + frascoHeight),
		CV_RGB(255, 255, 255), 2);

	return img;
}
