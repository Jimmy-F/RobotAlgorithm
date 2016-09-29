/*
 * InputParser.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: chris
 */

#include "InputParser.hpp"
#include "Detector.hpp"

InputParser::InputParser() :
		closeProgram(false), parsingComplete(false), color(""), shape(""),parsedInput() {
	initColorList();
	initShapeList();
}

InputParser::~InputParser() {
}

void InputParser::setIncommingInput(unsigned char key) {
	incommingInput.push_back(key);
}

void InputParser::checkInput() {
	for (auto &i : incommingInput) {
		if (i == 13) { //13 is Enter
			checkForWordExit(incommingInput);
			checkForWordCircel(incommingInput);
			checkForWordRechthoek(incommingInput);
			checkForWordHalveCircel(incommingInput);
			checkForWordVierkant(incommingInput);
			checkForWordDriehoek(incommingInput);
			incommingInput.clear();
		}
	}
	if(parsingComplete) {
		//ObjectFinder objectFinder(color,shape);
		parsingComplete = false;
	}
}

void InputParser::checkForWordExit(std::vector<unsigned char> input) {
	const unsigned char arrayLength = 5;
	unsigned char wordExit[arrayLength] = { 'e', 'x', 'i', 't', 13 };
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if (input[i] == wordExit[i]) {
			foundWord[i] = input[i];
		}
		else {
			break;
		}
	}
	if (arrayCompare(wordExit, foundWord, arrayLength)) {
		closeProgram = true;
	}
}

bool InputParser::getCloseProgram() {
	return closeProgram;
}

void InputParser::checkForWordCircel(std::vector<unsigned char> input) {
	const unsigned char arrayLength = 7;
	unsigned char wordExit[arrayLength] = { 'c', 'i', 'r', 'c', 'e', 'l', 32 };
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if (input[i] == wordExit[i]) {
			foundWord[i] = input[i];

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
				std::cout << shape << std::endl;
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
