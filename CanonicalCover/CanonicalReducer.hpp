#ifndef CANONICAL_REDUCER_HPP
#define CANONICAL_REDUCER_HPP

#include "stdafx.h"
#include "DataSet.hpp"

namespace canonical{

class CanonicalReducer
{
private:
	void refactorRules(std::set<Rule*>* rules);
	void removeReflexivity(std::set<Rule*>* rules);
public:
	void reduce(DataSet* dataSet);
};

}

#endif