/**
 * Implements a dataset parser which can
 * parse data that is in CSC 465 Data Mining Format
 * Parses from STDIN which is typicall set to a file
 */
#ifndef DATA_SET_PARSER
#define DATA_SET_PARSER

#include "stdafx.h"
#include "DataSet.hpp"
#include "IO.hpp"
#include "Attribute.hpp"
#include "Rule.hpp"

namespace canonical {

class DataSetParser
{
private:
	// The data set that is currently being constructed
	DataSet* m_dataSet;
	// An io utility class which is required to parse
	// the file
	IO* m_io;
	// Parses the attributes that exist in the dataset
	// Throws runtime error on failure
	void parseAttributes();
	// Parses the rules that exist in the dataset
	// throws runtime error on failure
	void parseRules();
	// Parses a single particular instance from
	// a c string
	Instance* parseInstance(char* input);
public:
	// Constructor
	DataSetParser(IO* io);
	// Public method which starts the chain of methods
	// that parse the data file
	DataSet* parseFromInput();
};

}

#endif