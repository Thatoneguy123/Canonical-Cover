/**
 * Class implements the basic flow of a canonical application. Handles
 * prompting user if they want to continue running, parsing cmdline args,
 * and getting the file the user wants to parse.
 */
#ifndef CANONICAL_APPLICATION_HPP
#define CANONICAL_APPLICATION_HPP

#include "stdafx.h"
#include "IO.hpp"
#include "DataSetParser.hpp"
#include "CanonicalReducer.hpp"

using namespace std;

namespace canonical {

class CanonicalApplication
{
private:
	// Pointer to the dataset parser that will be used
	// to parse the users inputted file
	DataSetParser* m_dataSetParser;
	// Pointer to an IO object which provides some basic
	// io functions
	IO* m_io;
	// Pointer to reducer which will modify the data set
	// to reduce it to its minimal canonical form
	CanonicalReducer* m_canonicalReducer;

	// File descriptor to console input
	// used to save fd when switched between inputs
	int m_consoleFd;
	// File to read input from
	FILE* m_file;

	// Method parses command line arguments for running the application
	// -h || -H will display a usage list while -f || -F followed by a 
	// file name will load that single file and reduce it to canonical form
	void parseCmdLineArgs(int argc, char* argv[]);
	// Echos the usage for the program to stdout
	void usage();
	// Prints the set to stdio as well as a user specifed output file
	// Does not nessecarily print reduced form if set has not been
	// reduced yet.
	void printSet(DataSet* dataSet);
	// Takes a c string to a file name and sets STDIN to read from that file
	void getFile(char* fileArg);
	// Ends a parsing session, ensures all File descriptors are reset and that
	// all memory that needs to be deleted is deleted
	void endParseSession();
	// Prompts the user to see if they would like to run the program again
	// with another data set
	bool getRunAgain();
public:
	// Default constructor
	CanonicalApplication();
	// Destrcutor
	~CanonicalApplication();
	// Runs the canonical application with cmd line args
	void run(int argc, char* argv[]);
};

}

#endif