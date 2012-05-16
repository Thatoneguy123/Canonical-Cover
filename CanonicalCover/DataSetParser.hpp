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
	DataSet* m_dataSet;
	IO* m_io;
	void parseAttributes();
	void parseRules();
	Instance* parseInstance(char* input);
public:
	DataSetParser(IO* io);
	DataSet* parseFromInput();
};

}

#endif