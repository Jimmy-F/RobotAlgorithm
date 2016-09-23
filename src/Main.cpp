#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "InputParser.hpp"

int main(int argc, char **argv) {
	InputParser inputParser;
	cv::namedWindow("Window", cv::WINDOW_AUTOSIZE);
	std::string input;
	while (inputParser.getCloseProgram() == false) {
		if(inputParser.getCloseProgram()) {
			return 0;
		}
		std::getline(std::cin, input);
		std::stringstream iS(input);
		inputParser.parseInput(iS);
	}
}
