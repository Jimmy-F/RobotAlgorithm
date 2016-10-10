/*
 * InputParser.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: chris
 */

#include "InputParser.hpp"
#include "Detector.hpp"


InputParser::InputParser(std::string image) :
		closeProgram(false), parsingComplete(false), color(""), shape(""),parsedInput()  {
	img = image;
	initColorList();
	initShapeList();
}

InputParser::~InputParser() {
}

void InputParser::parseInput(std::stringstream& input) {
	std::string inputShape;
	input >> inputShape;
	checkForWordExit(inputShape);
	for(unsigned char i = 0; i < shapeList.size(); i++) {
		if(inputShape == shapeList[i]) {
			if(shapeList[i] == "halve") {
				checkForWordHalveCircel(input);
			}
			else {
				shape = shapeList[i];
				std::cout << shape << " ";
				searchForColor(input);
			}
		}
	}
}

void InputParser::searchForColor(std::stringstream& input) {
	std::string inputColor;
	input >> inputColor;
	for(unsigned char i = 0; i < colorList.size(); i++) {
		if(inputColor == colorList[i]) {
			color = colorList[i];
			std::cout << color << std::endl;
			Detector d(shape, color, 3);
			cv::Mat image = cv::imread(img,1);
			d.findShapes(image);
			if (cv::waitKey(10) == 27)
			cv::destroyAllWindows();
			break;
		}
	}
}

void InputParser::checkForWordHalveCircel(std::stringstream& input) {
	std::string inputShape;
	input >> inputShape;
	if(inputShape == "circel") {
		shape = "halve circel";
		std::cout << shape << std::endl;
		searchForColor(input);
	}
}

bool InputParser::getCloseProgram() {
	return closeProgram;
}

void InputParser::initColorList() {
	colorList.push_back("wit");
	colorList.push_back("zwart");
	colorList.push_back("rood");
	colorList.push_back("groen");
	colorList.push_back("blauw");
	colorList.push_back("geel");
}

void InputParser::checkForWordExit(std::string input) {
	if(input == "exit") {
		closeProgram = true;
	}
}

void InputParser::initShapeList() {
	shapeList.push_back("circel");
	shapeList.push_back("vierkant");
	shapeList.push_back("driehoek");
	shapeList.push_back("rechthoek");
	shapeList.push_back("halve");
}
