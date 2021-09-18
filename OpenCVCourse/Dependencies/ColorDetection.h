#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include "Color.h"
#include "Imagen.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#define rep(i, a, b) for (int(i) = (a); (i) < (b); ++(i))

class ColorDetection
{
private:
	cv::Mat hsvImg;
	std::pair<cv::Scalar, cv::Scalar> getLowAndHighHSV(Color color);
	void getColorLiquidosForSingleColor(Color color);
	std::vector<Imagen> liquidos;
	std::vector<Imagen> frascos;

public:
	ColorDetection(cv::Mat img_) {
		hsvImg = img_;
	}
	void detectAllColors();
	std::vector<Imagen> getLiquidos() { return liquidos; };
	std::vector<Imagen> getFrascos() { return frascos; };

};

#endif