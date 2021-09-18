#ifndef IMAGE_MANIPULATION_H
#define IMAGE_MANIPULATION_H

#include "Color.h"
#include "Move.h"
#include "Imagen.h"
#include "AlgorithmUtils.h"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#define pb push_back
#define mp make_pair
#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define trav(a, x) for (auto(a) : (x))
typedef std::vector<int> vi;

namespace ImageManipulation
{
	// RENDERING VARIABLES
	const int marginX = 15;
	const int marginY = 50;
	const int frascoContainerThickness = 3;
	const int liquidoWidth = 74;
	const int liquidoHeight = 60;
	const int topEmptyFrascoHeight = 40;
	const int frascoWidth = liquidoWidth + frascoContainerThickness * 2;
	const int frascoHeight = liquidoHeight * AlgorithmUtils::COLORES_POR_FRASCO + topEmptyFrascoHeight;
	const int marginYMid = marginY;

	bool imageComparator(Imagen& a, Imagen& b);
	cv::Scalar getColorRGBScalar(Color color);
	cv::Mat putInstructionsOnImage(std::vector<std::vector<Imagen>> frasquitos, Move move, cv::Mat img);
	std::vector<cv::Mat> getSolutionImages(std::vector<Move> moves, std::vector<std::vector<Imagen>> frasquitos, cv::Mat img);
	std::pair <cv::Mat, std::vector<std::vector<Imagen>>> getInitialImageAndMatrix(std::vector<Imagen> frascos, std::vector<Imagen> liquidos);
	std::pair <cv::Mat, std::vector<std::vector<Imagen>>> getInitialImageAndMatrix(std::vector<std::vector<Color>> colorMatrix);
};

#endif