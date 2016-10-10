#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "InputParser.hpp"
#include "Detector.hpp"

int main(int argc, char* argv[]) {
	InputParser inputParser("/home/jimmy/Pictures/vormpjes.jpg");
	//cv::Mat img = cv::imread("/home/jimmy/Pictures/vormpjes.jpg",1);

	cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);

	//cv::waitKey(0);

	if (argc > 2) {
		std::cout << "You only need to supply one argument to this program.";
		return 0;
	} else if (argc > 1) {
		std::ifstream batchFile;
		batchFile.open(argv[1]);

		if (batchFile.fail()) {
			std::cout << "Batchfile could not be loaded." << std::endl;
			return 0;
		} else {
			std::string batchFileString;
			batchFileString = argv[1];
			while (!batchFile.eof()) {
				std::getline(batchFile, batchFileString);
				std::stringstream commentRemover(batchFileString);
				std::getline(commentRemover, batchFileString, '#');
				std::stringstream inputStringBatch(batchFileString);
				inputParser.parseInput(inputStringBatch);
			}
			batchFile.close();
			return 0;
		}
	} else {
		while (inputParser.getCloseProgram() == false) {
			if (inputParser.getCloseProgram()) {
				return 0;
			}
			std::string input;
			std::getline(std::cin, input);
			std::stringstream inputString(input);
			inputParser.parseInput(inputString);
		}
	}
}
