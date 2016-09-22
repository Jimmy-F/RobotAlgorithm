/*
 * InputParser.hpp
 *
 *  Created on: Sep 21, 2016
 *      Author: chris
 */

#ifndef SRC_InputParser_HPP_
#define SRC_InputParser_HPP_

#include <vector>
#include <iostream>
#include <string>

class InputParser {
public:
	InputParser();
	virtual ~InputParser();
	void setIncommingInput(unsigned char key);
	void checkInput();

	void checkForWordExit(std::vector<unsigned char> input);
	void checkForWordHalveCircel(std::vector<unsigned char> input);
	void checkForWordCircel(std::vector<unsigned char> input);
	void checkForWordRechthoek(std::vector<unsigned char> input);
	void checkForWordVierkant(std::vector<unsigned char> input);
	void checkForWordDriehoek(std::vector<unsigned char> input);

	void checkForColorWit(const unsigned char startPosition,std::vector<unsigned char> input);
	void checkForColorRood(const unsigned char startPosition,std::vector<unsigned char> input);
	void checkForColorGroen(const unsigned char startPosition,std::vector<unsigned char> input);
	void checkForColorBlauw(const unsigned char startPosition,std::vector<unsigned char> input);
	void checkForColorZwart(const unsigned char startPosition,std::vector<unsigned char> input);
	void checkForColorGeel(const unsigned char startPosition,std::vector<unsigned char> input);

	bool arrayCompare(unsigned char arrayOne[],unsigned char arrayTwo[],unsigned char arrayLength);

	bool getCloseProgram();
private:
	std::vector<unsigned char> incommingInput;
	bool closeProgram;
	bool parsingComplete;
	std::string color;
	std::string shape;
};

#endif /* SRC_InputParser_HPP_ */
