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
	DataSetParser* m_dataSetParser;
	IO* m_io;
	CanonicalReducer* m_canonicalReducer;

	void parseCmdLineArgs(int argc, char* argv[]);
	void usage();
public:
	CanonicalApplication();
	~CanonicalApplication();
	void run(int argc, char* argv[]);
};

}

#endif