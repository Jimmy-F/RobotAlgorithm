#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "InputParser.hpp"

int main() {
	InputParser inputParser;
	cv::namedWindow("Window",cv::WINDOW_AUTOSIZE);

	while (true) {
		inputParser.setIncommingInput(cv::waitKey());
		inputParser.checkInput();
		if(inputParser.getCloseProgram()) {
			return 0;
		}
	}
}
