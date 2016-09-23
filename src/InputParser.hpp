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
#include <sstream>

class InputParser {
public:
	InputParser();
	virtual ~InputParser();
	void parseInput(std::stringstream& input);
	bool getCloseProgram();
	void initColorList();
	void initShapeList();

	void checkForWordExit(std::string input);
	void checkForWordHalveCircel(std::stringstream& input);
	void searchForColor(std::stringstream& input);
private:
	bool closeProgram;
	bool parsingComplete;
	std::string color;
	std::string shape;
	std::vector<std::string> parsedInput;
 	std::vector<std::string> colorList;
	std::vector<std::string> shapeList;
};

#endif /* SRC_InputParser_HPP_ */
