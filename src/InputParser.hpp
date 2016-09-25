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
	/**
	 * Parses the console input.
	 * @Param input A stringstream with user input.
	 */
	void parseInput(std::stringstream& input);

	/**
	 * Gets the boolean that decides if the program must be terminated.
	 * @return A boolean that decides if the program must be terminated.
	 */
	bool getCloseProgram();

private:
	/**
	 * Initializes the colors for the input parser.
	 */
	void initColorList();


	/**
	 * Initializes the shapes for the input parser.
	 */
	void initShapeList();

	/**
	 * Searches for the word Exit in the given string.
	 * @param input A string with parsed user input.
	 */
	void checkForWordExit(std::string input);

	/**
	 * Checks the input variable for the word Circel.
	 * @param input A stringstream with user input.
	 */
	void checkForWordHalveCircel(std::stringstream& input);

	/**
	 * Searches the user input for colors.
	 * @param input A stringstream with user input.
	 */
	void searchForColor(std::stringstream& input);

	bool closeProgram;
	bool parsingComplete;
	std::string color;
	std::string shape;
	std::vector<std::string> parsedInput;
 	std::vector<std::string> colorList;
	std::vector<std::string> shapeList;
};

#endif /* SRC_InputParser_HPP_ */
