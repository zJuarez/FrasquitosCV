#include "Dependencies/ImageManipulation.h"
#include "Dependencies/ColorDetection.h"
#include "Dependencies/AlgorithmV2.h"
#include "Dependencies/AlgorithmV1.h"

#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))
#define trav(a, x) for (auto(a) : (x))
#define pb push_back
#define mp make_pair
#define mt make_tuple
typedef std::vector<int> vi;

using namespace cv;

bool v2 = true;
bool v1 = true;

const std::string imagePath = "Resources/frasquitos5.jpeg";

void mainHSVCalibration() {

	Mat img = imread(imagePath);
	Mat imgHSV, mask;
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	Rect roi(0, img.size().height * 0.2, img.size().width,
		img.size().height * 0.65);
	Mat imgCrop = img(roi);

	cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", imgCrop);
		// imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}

std::vector<std::string> split(std::string str, char pattern) {

	int posInit = 0;
	int posFound = 0;
	std::string splitted;
	std::vector<std::string> results;

	while (posFound >= 0) {
		posFound = str.find(pattern, posInit);
		splitted = str.substr(posInit, posFound - posInit);
		posInit = posFound + 1;
		results.push_back(splitted);
	}

	return results;
}

int mainText() {

	int n;
	std::cin >> n;
	int frascosVacios = 2;
	std::vector<Color> frasquitoVacio(AlgorithmUtils::COLORES_POR_FRASCO, Color::VACIO);
	std::vector<std::vector<Color>> frasquitosOriginal(n + AlgorithmUtils::FRASCOS_VACIOS, frasquitoVacio);
	rep(i, 0, n) {
		rep(j, 0, AlgorithmUtils::COLORES_POR_FRASCO) {
			int color;
			std::cin >> color;
			frasquitosOriginal[i][j] = (Color)color;
		}
	}
	std::pair <cv::Mat, std::vector<std::vector<Imagen>>> mappedImgAndMatrix = ImageManipulation::getInitialImageAndMatrix(frasquitosOriginal);

	cv::Mat mappedImg = mappedImgAndMatrix.first;
	std::vector<std::vector<Imagen>> matrix = mappedImgAndMatrix.second;

	AlgorithmUtils::initialSummary(matrix);
	imshow("Is this okay?", mappedImg);
	waitKey(0);

	std::vector<Move> emptyMoves;

	if (v2) {

		AlgorithmV2 botV2(matrix);
		std::cout << "V2 - TRYING: " << std::endl;

		if (botV2.solve(emptyMoves)) {
			std::vector<Mat> solutionImages = ImageManipulation::getSolutionImages(botV2.getSolution(), matrix, mappedImg);
			std::cout << solutionImages.size() << std::endl;
			trav(img, solutionImages) {
				imshow("Solution", img);
				waitKey(0);
			}
			return 0;
		}

	}
	if (v1) {
		rep(i, 0, matrix.size()) {
			std::cout << "V1 - TRYING WITH: " + std::to_string(i) << std::endl;
			AlgorithmV1 botV1(matrix, i);
			if (botV1.solve(emptyMoves)) {
				std::vector<Mat> solutionImages = ImageManipulation::getSolutionImages(botV1.getSolution(), matrix, mappedImg);
				std::cout << solutionImages.size() << std::endl;
				trav(img, solutionImages) {
					imshow("Solution", img);
					waitKey(0);
				}
				return 0;
			}
		}
	}

	putText(mappedImg, "FAIL", Point2i(30, 80), 0, 2.2, CV_RGB(255, 0, 0), 2);
	std::cout << "I SUCK" << std::endl;
	imshow("ERROR", mappedImg);
	waitKey(0);

	return 0;
}

int main() {

	Mat img = imread(imagePath);
	Rect roi(0, img.size().height * 0.2, img.size().width,
		img.size().height * 0.65);
	Mat imgCrop = img(roi);

	Mat bgImg(imgCrop.size(), CV_8UC3, Scalar(0, 0, 0)), imgHSV;

	cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);

	ColorDetection colorDetection(imgHSV);
	colorDetection.detectAllColors();


	std::pair <cv::Mat, std::vector<std::vector<Imagen>>> mappedImgAndMatrix = ImageManipulation::getInitialImageAndMatrix(colorDetection.getFrascos(), colorDetection.getLiquidos());

	cv::Mat mappedImg = mappedImgAndMatrix.first;
	std::vector<std::vector<Imagen>> matrix = mappedImgAndMatrix.second;

	AlgorithmUtils::initialSummary(matrix);
	imshow("Is this okay?", mappedImg);
	waitKey(0);

	std::vector<Move> emptyMoves;

	if (v2) {

		AlgorithmV2 botV2(matrix);
		std::cout << "V2 - TRYING: " << std::endl;

		if (botV2.solve(emptyMoves)) {
			std::vector<Mat> solutionImages = ImageManipulation::getSolutionImages(botV2.getSolution(), matrix, mappedImg);
			std::cout << solutionImages.size() << std::endl;
			trav(img, solutionImages) {
				imshow("Solution", img);
				waitKey(0);
			}
			return 0;
		}

	}
	if (v1) {
		rep(i, 0, matrix.size()) {
			std::cout << "V1 - TRYING WITH: " + std::to_string(i) << std::endl;
			AlgorithmV1 botV1(matrix, i);
			if (botV1.solve(emptyMoves)) {
				std::vector<Mat> solutionImages = ImageManipulation::getSolutionImages(botV1.getSolution(), matrix, mappedImg);
				std::cout << solutionImages.size() << std::endl;
				trav(img, solutionImages) {
					imshow("Solution", img);
					waitKey(0);
				}
				return 0;
			}
		}
	}

	putText(mappedImg, "FAIL", Point2i(30, 80), 0, 2.2, CV_RGB(255, 0, 0), 2);
	std::cout << "I SUCK" << std::endl;
	imshow("ERROR", mappedImg);
	waitKey(0);

	return 0;
}
