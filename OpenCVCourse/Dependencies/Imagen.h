#ifndef IMAGE_H
#define IMAGE_H
#include "Color.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

class Imagen {
private:
	Color color;
	cv::Point2i position;
	cv::Rect rect;
public:
	Imagen() { color = Color::VACIO; }
	Imagen(Color color_) { color = color_; }
	Imagen(Color color_, cv::Rect rect_, int x, int y) {
		color = color_;
		rect = rect_;
		position = cv::Point2i(x, y);
	}
	void setColor(Color color_) { color = color_; }
	Color getColor() { return color; }
	cv::Point2i getPoint() { return position; }
	cv::Rect getRect() { return rect; }
};
#endif