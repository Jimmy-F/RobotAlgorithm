/*
 * InputParser.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: chris
 */

#include "InputParser.hpp"

InputParser::InputParser() :
		incommingInput(), closeProgram(false),parsingComplete(false), color(""),shape("") {
	// TODO Auto-generated constructor stub
}

InputParser::~InputParser() {
	// TODO Auto-generated destructor stub
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
		}
		else {
			break;
		}
	}
	if (arrayCompare(wordExit, foundWord, arrayLength)) {
		shape = "CIRCLE";
		checkForColorWit(arrayLength, input);
		checkForColorRood(arrayLength, input);
		checkForColorGroen(arrayLength, input);
		checkForColorBlauw(arrayLength, input);
		checkForColorZwart(arrayLength, input);
		checkForColorGeel(arrayLength, input);
	}
}

void InputParser::checkForWordVierkant(std::vector<unsigned char> input) {
	const unsigned char arrayLength = 9;
	unsigned char wordExit[arrayLength] = { 'v', 'i', 'e', 'r', 'k', 'a','n','t', 32 };
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
		shape = "SQUARE";
		checkForColorWit(arrayLength, input);
		checkForColorRood(arrayLength, input);
		checkForColorGroen(arrayLength, input);
		checkForColorBlauw(arrayLength, input);
		checkForColorZwart(arrayLength, input);
		checkForColorGeel(arrayLength, input);
	}
}

void InputParser::checkForWordRechthoek(std::vector<unsigned char>input) {
	const unsigned char arrayLength = 10;
	unsigned char wordExit[arrayLength] = { 'r', 'e', 'c', 'h', 't', 'h','o','e','k', 32 };
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
		shape = "RECTANGLE";
		checkForColorWit(arrayLength, input);
		checkForColorRood(arrayLength, input);
		checkForColorGroen(arrayLength, input);
		checkForColorBlauw(arrayLength, input);
		checkForColorZwart(arrayLength, input);
		checkForColorGeel(arrayLength, input);
	}
}

void InputParser::checkForWordHalveCircel(std::vector<unsigned char> input) {
	const unsigned char arrayLength = 13;
	unsigned char wordExit[arrayLength] = { 'h', 'a', 'l', 'v', 'e',32,'c','i','r','c','e','l',32};
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
		shape = "HALFCIRCLE";
		checkForColorWit(arrayLength, input);
		checkForColorRood(arrayLength, input);
		checkForColorGroen(arrayLength, input);
		checkForColorBlauw(arrayLength, input);
		checkForColorZwart(arrayLength, input);
		checkForColorGeel(arrayLength, input);
	}
}

void InputParser::checkForWordDriehoek(std::vector<unsigned char> input) {
	const unsigned char arrayLength = 9;
	unsigned char wordExit[arrayLength] = { 'd', 'r', 'i', 'e', 'h','o','e','k', 32 };
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
		shape = "TRIANGLE";
		checkForColorWit(arrayLength, input);
		checkForColorRood(arrayLength, input);
		checkForColorGroen(arrayLength, input);
		checkForColorBlauw(arrayLength, input);
		checkForColorZwart(arrayLength, input);
		checkForColorGeel(arrayLength, input);
	}
}

bool InputParser::arrayCompare(unsigned char arrayOne[],
		unsigned char arrayTwo[], unsigned char arrayLength) {
	for (unsigned char i = 0; i < arrayLength; ++i) {
		if (arrayOne[i] != arrayTwo[i]) {
			return false;
		}
	}
	return true;
}

void InputParser::checkForColorWit(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 4;
	unsigned char wordWit[arrayLength] = {'w','i','t',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordWit[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordWit,foundWord,arrayLength)) {
		color = "WHITE";
		parsingComplete = true;
	}
}

void InputParser::checkForColorRood(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 5;
	unsigned char wordRood[arrayLength] = {'r','o','o','d',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordRood[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordRood,foundWord,arrayLength)) {
		color = "RED";
		parsingComplete = true;
	}
}

void InputParser::checkForColorGroen(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 6;
	unsigned char wordGroen[arrayLength] = {'g','r','o','e','n',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordGroen[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordGroen,foundWord,arrayLength)) {
		color = "GREEN";
		parsingComplete = true;
	}
}

void InputParser::checkForColorBlauw(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 6;
	unsigned char wordBlauw[arrayLength] = {'b','l','a','u','w',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordBlauw[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordBlauw,foundWord,arrayLength)) {
		color = "BLUE";
		parsingComplete = true;
	}
}

void InputParser::checkForColorZwart(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 6;
	unsigned char wordZwart[arrayLength] = {'z','w','a','r','t',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordZwart[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordZwart,foundWord,arrayLength)) {
		color = "BLACK";
		parsingComplete = true;
	}
}

void InputParser::checkForColorGeel(const unsigned char startPosition,std::vector<unsigned char> input) {
	const unsigned char arrayLength = 5;
	unsigned char wordGeel[arrayLength] = {'g','e','e','l',13};
	unsigned char foundWord[arrayLength];
	for (unsigned char i = 0; i < arrayLength; i++) {
		if(input[i+startPosition] == wordGeel[i]) {
			foundWord[i] = input[i+startPosition];
		}
		else {
			break;
		}
	}
	if(arrayCompare(wordGeel,foundWord,arrayLength)) {
		color = "YELLOW";
		parsingComplete = true;
	}
}
