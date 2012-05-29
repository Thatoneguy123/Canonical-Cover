/**
 * IO class provides some basic utilitys
 * for gathering input
 */
#ifndef IO_HPP
#define IO_HPP

#include "stdafx.h"

using namespace std;

namespace canonical{

class IO
{
private:
public:
	IO();
	// Pauses and prompts the user to press "any key"
	void pause();
	// Clears the screen
	void clear();
	// Reads until end of line is found then positions
	// buffer at beginning of next line
	void skipLine();
	// Reads a single char and checks to see that it
	// is a valid integer. Throws runtime error if not
	// an integer
	int readInt();
	// Checks if next characters is the end of file character
	bool eof();
	// Reads a single character
	char readChar();
	// Reads a string seperated by whitespace or \n. If \n is read
	// the method will return null. All memory returned must be
	// deleted
	char* readString();
};

}

#endif

// Portability
#ifdef __linux__
	#define CLEARSCREEN clear()
#endif

#ifdef _WIN32
	#define CLEARSCREEN system("cls")
#endif