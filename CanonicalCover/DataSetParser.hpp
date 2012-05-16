#ifndef DATA_SET_PARSER
#define DATA_SET_PARSER

#include "stdafx.h"
#include "DataSet.hpp"
#include "IO.hpp"
#include "Attribute.hpp"

namespace canonical {

class DataSetParser
{
private:
	DataSet* m_dataSet;
	IO* m_io;
	void parseAttributes();
public:
	DataSetParser(IO* io);
	DataSet* parseFromInput();
};

}

#endif