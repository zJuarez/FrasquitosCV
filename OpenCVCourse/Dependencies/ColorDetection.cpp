#include "ColorDetection.h"

std::pair<cv::Scalar, cv::Scalar> ColorDetection::getLowAndHighHSV(Color color) {
	switch (color) {
	case CAFE:
		return std::make_pair(cv::Scalar(0, 206, 108), cv::Scalar(33, 255, 139));
	case AZUL:
		return std::make_pair(cv::Scalar(101, 180, 99), cv::Scalar(128, 255, 255));
	case VERDE_CESPED:
		return std::make_pair(cv::Scalar(33, 187, 0), cv::Scalar(63, 255, 255));
	case ROSA:
		return std::make_pair(cv::Scalar(113, 104, 210), cv::Scalar(179, 227, 252));
	case MORADO:
		return std::make_pair(cv::Scalar(138, 165, 135), cv::Scalar(170, 255, 255));
	case VERDE_FOSFO:
		return std::make_pair(cv::Scalar(63, 82, 135), cv::Scalar(75, 255, 255));
	case CELESTE:
		return std::make_pair(cv::Scalar(100, 153, 210), cv::Scalar(134, 212, 252));
	case GRIS:
		return std::make_pair(cv::Scalar(0, 0, 87), cv::Scalar(179, 111, 104)); // v max 121
	case VERDE_FUERTE:
		return std::make_pair(cv::Scalar(41, 180, 75), cv::Scalar(93, 255, 255));
	case NARANJA:
		return std::make_pair(cv::Scalar(12, 135, 203), cv::Scalar(21, 201, 252));
	case ROJO:
		return std::make_pair(cv::Scalar(0, 206, 0), cv::Scalar(11, 255, 255));
	case AMARILLO:
		return std::make_pair(cv::Scalar(22, 104, 210), cv::Scalar(60, 227, 252));
	case FRASCO:
		return std::make_pair(cv::Scalar(0, 0, 161), cv::Scalar(179, 45, 219));
	default:
		return std::make_pair(cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0));
	}
}

void ColorDetection::getColorLiquidosForSingleColor(Color color) {
	std::pair<cv::Scalar, cv::Scalar> lowAndHigh = getLowAndHighHSV(color);
	cv::Scalar low = lowAndHigh.first, high = lowAndHigh.second;
	cv::Mat mask;
	cv::inRange(hsvImg, low, high, mask);
	std::vector<std::vector<cv::Point>> contours;
	findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contours.size(); i++) {
		cv::Rect boundRect = boundingRect(contours[i]);
		if (boundRect.area() > 1000) {
			if (color == Color::FRASCO)
				frascos.emplace_back(color, boundRect,
					boundRect.x + boundRect.width / 2,
					boundRect.y + boundRect.height / 2);
			else
				liquidos.emplace_back(color, boundRect,
					boundRect.x + boundRect.width / 2,
					boundRect.y + boundRect.height / 2);
		}
	}
	// imshow("mask from " + colors[color], mask);
	// waitKey(10);
}

void ColorDetection::detectAllColors() {
	rep(iColor, 0, Color::VACIO) {
		Color color = static_cast<Color>(iColor);
		getColorLiquidosForSingleColor(color);
	}
}