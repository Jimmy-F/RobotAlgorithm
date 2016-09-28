//
// Created by jimmy on 21-9-16.
//

#include "Detector.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>


Detector::Detector(const std::string aShape, const std::string aColor) :
		shape(aShape), color(aColor) {
	std::pair<cv::Scalar, cv::Scalar> range = getColorRange(aColor);
	minColor = range.first;
	maxColor = range.second;
}

std::vector<std::vector<cv::Point> > Detector::findShapes(cv::Mat& img) {


	//TODO filter and return the contours.
	cv::Mat thresh = getFilteredImg(img);

	std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    clock_t startTime = clock();
    cv::findContours(thresh.clone(), contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    cv::Canny(thresh, thresh, 200,20);
	cv::namedWindow("Thresh",cv::WINDOW_AUTOSIZE); cv::imshow("Thresh",thresh);




	std::vector<cv::Point> approx;

    std::vector<std::vector<cv::Point>> ret_contours;

    for (unsigned int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;

        if (approx.size() == 3 && shape == "driehoek")
        {
            cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );
        	std::pair<double, double> c = getCenter(contours[i]);
        	setLabel(img, "("+std::to_string((long)c.first)+ "," + std::to_string((long)c.second)+")", contours[i]);   // Triangles
            ret_contours.push_back(contours[i]);

            std::cout << "surface: " << getSurface(contours[i]) << std::endl;

           // markContours(img, contours[i], cv::Scalar(200,200,200));
        }
        else if (approx.size() == 4 &&(shape == "vierkant" || shape == "rechthoek"))
        {
        	cv::Rect r = cv::boundingRect(contours[i]);
            // Number of vertices of polygonal curve
            int vtc = approx.size();

            // Get the cosines of all corners
            std::vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));

            // Sort ascending the cosine values
            std::sort(cos.begin(), cos.end());

            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();

            // Use the degrees obtained above and the number of vertices
            // to determine the shape of the contour
            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3 && shape == "vierkant" &&
            	std::abs(1 - (double)r.width / r.height) <= 0.2) {
                std::pair<double, double> c = getCenter(contours[i]);
            	setLabel(img, "("+std::to_string((long)c.first)+ "," + std::to_string((long)c.second)+")", contours[i]);
                std::cout << "surface: " << getSurface(contours[i]) << std::endl;
                cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );

                ret_contours.push_back(contours[i]);
            }
            else if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3 && shape == "rechthoek" &&
            	std::abs(1 - (double)r.width / r.height) >= 0.2) {
                std::pair<double, double> c = getCenter(contours[i]);
            	setLabel(img, "("+std::to_string((long)c.first)+ "," + std::to_string((long)c.second)+")", contours[i]);
                std::cout << "surface: " << getSurface(contours[i]) << std::endl;
                cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );

               //markContours(img, contours[i], cv::Scalar(200,200,200));
                ret_contours.push_back(contours[i]);
            }

        }
        else if (shape == "circel")
        {
            // Detect and label circles
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);

            int radius = r.width / 2;

            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2
				&& shape == "circel") {
                cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );
            	std::pair<double, double> c = getCenter(contours[i]);
            	            	setLabel(img, "("+std::to_string((long)c.first)+ "," + std::to_string((long)c.second)+")", contours[i]);
                std::cout << "x: " << c.first << std::endl;
                std::cout << "y: " << c.second << std::endl;
                std::cout << "surface: " << getSurface(contours[i]) << std::endl;

                clock_t endTime = clock();
                clock_t clockTicksTaken = endTime - startTime;
                double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
                std::cout << "Tijd: " << timeInSeconds << std::endl;
                std::cout << "Ticks: " << clockTicksTaken << std::endl;
                ret_contours.push_back(contours[i]);

            }
            else if (std::abs(((double)r.width / r.height >= 0.3)) && shape == "halve circel") {
                cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );
                //cv::rectangle(img, r, cv::Scalar(0,0,0), 1, 8, 0);
            }
        }
        else if (shape == "halve circel") {
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);

            int radius = r.width;

            if (std::abs((double)r.width / r.height) >= 0.3 &&
                std::abs(1 - (area / ((CV_PI * std::pow(radius, 2))/2))) <= 0.2) {
                cv::drawContours( img, contours, i, cv::Scalar(200,200,200), 2, 8, hierarchy, 0 );
            	std::pair<double, double> c = getCenter(contours[i]);
            	            	setLabel(img, "("+std::to_string((long)c.first)+ "," + std::to_string((long)c.second)+")", contours[i]);
                std::cout << "x: " << c.first << std::endl;
                std::cout << "y: " << c.second << std::endl;
                std::cout << "surface: " << getSurface(contours[i]) << std::endl;

                clock_t endTime = clock();
                clock_t clockTicksTaken = endTime - startTime;
                double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
                std::cout << "Tijd: " << timeInSeconds << std::endl;
                std::cout << "Ticks: " << clockTicksTaken << std::endl;
                ret_contours.push_back(contours[i]);

            }

        }

    }

    if (ret_contours.size() == 0 ) {
    	std::cout << "Er zijn geen objecten gevonden van het gegeven type" << std::endl;
    }
    return ret_contours;
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

cv::Mat Detector::getFilteredImg(cv::Mat& img) {

	cv::Mat blurred_img;
	cv::GaussianBlur(img, blurred_img, cv::Size(5,5), 1.5, 1.5);
	cv::medianBlur(blurred_img, blurred_img, 5);

	//cv::GaussianBlur(blokjes, blur_blokjes, cv::Size(5,5), 5, 5);
	cv::cvtColor(blurred_img, blurred_img, cv::COLOR_BGR2HSV);

	cv::Mat thresh;
	if (color == "rood") {
		cv::Mat1b mask1, mask2;
		cv::inRange(blurred_img, cv::Scalar(0, 70, 50), cv::Scalar(10, 255, 255), mask1);
		cv::inRange(blurred_img, minColor, maxColor, mask2);

		thresh = mask1 | mask2;
	}
    else {
    	cv::inRange(blurred_img, minColor, maxColor, thresh);
    }
	return thresh;
}

Detector::~Detector() {

}

void Detector::setLabel(cv::Mat& im, const std::string label,
		std::vector<cv::Point>& contour) {
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.3;
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
		colorRange.first = cv::Scalar(170, 200, 100);
		colorRange.second = cv::Scalar(179, 255, 255);
	} else if (color == "groen") {
		colorRange.first = cv::Scalar(40, 150, 50);
		colorRange.second = cv::Scalar(70, 255, 255);
	} else if (color == "blauw") {
		colorRange.first = cv::Scalar(80, 180, 90);
		colorRange.second = cv::Scalar(130, 255, 255);
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

