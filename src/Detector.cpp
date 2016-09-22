//
// Created by jimmy on 21-9-16.
//

#include "Detector.hpp"

Detector::Detector(const std::string aShape, const std::string aColor) :
		shape(aShape), color(aColor) {
	std::pair<cv::Scalar, cv::Scalar> range = getColorRange(aColor);
	minColor = range.first;
	maxColor = range.second;
}

std::vector<std::vector<cv::Point> > Detector::findShapes(cv::Mat& img) {
	//TODO filter and return the contours.
}

void Detector::markContours(cv::Mat& img, std::vector<cv::Point>& contour,
		cv::Scalar color) {
	cv::drawContours(img, contour, -1, color, 2);
}

std::pair<double, double> Detector::getCenter(std::vector<cv::Point>& contour) {

	cv::Moments mu;
	mu = cv::moments(contour, false);
	cv::Point2f mc;
	mc = cv::Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
	std::pair<double, double> coordinates { mc.x, mc.y };
	return coordinates;

}

double Detector::getSurface(std::vector<cv::Point>& contour) {
	return cv::contourArea(contour);
}

Detector::~Detector() {

}

double Detector::getSurfaceCircle(std::vector<cv::Point>& contour) {
	//TODO Get the surface of the circle by evaluating the points and using M_PI
	return 0;
}

double Detector::getSurfaceRectangle(std::vector<cv::Point>& contour) {
	//TODO Get the surface by getting the length and width using the points.
	return 0;
}

double Detector::getSurfaceTriangle(std::vector<cv::Point>& contour) {
	//TODO Get the surface by getting the the half of the width and the length then use pythagoras
	return 0;
}

void Detector::setLabel(cv::Mat& im, const std::string label,
		std::vector<cv::Point>& contour) {
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness,
			&baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2),
			r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline),
			pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255),
			CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

double Detector::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1 * dx2 + dy1 * dy2)
			/ sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

std::pair<cv::Scalar, cv::Scalar> Detector::getColorRange(std::string color) {
	std::pair<cv::Scalar, cv::Scalar> colorRange { cv::Scalar(0, 0, 0),
			cv::Scalar(0, 0, 0) };

	if (color == "rood") {
		colorRange.first = cv::Scalar(179, 200, 120);
		colorRange.second = cv::Scalar(179, 255, 255);
	} else if (color == "groen") {
		colorRange.first = cv::Scalar(60, 150, 50);
		colorRange.second = cv::Scalar(60, 255, 255);
	} else if (color == "blauw") {
		colorRange.first = cv::Scalar(100, 180, 100);
		colorRange.second = cv::Scalar(120, 255, 255);
	} else if (color == "geel") {
		colorRange.first = cv::Scalar(25, 180, 180);
		colorRange.second = cv::Scalar(30, 255, 255);
	} else if (color == "zwart") {
		colorRange.first = cv::Scalar(0, 0, 0);
		colorRange.second = cv::Scalar(179, 255, 25);
	} else if (color == "wit") {
		colorRange.first = cv::Scalar(0, 0, 220);
		colorRange.second = cv::Scalar(179, 40, 255);
	}

	return colorRange;
}

