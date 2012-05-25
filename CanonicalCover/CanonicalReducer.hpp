#ifndef CANONICAL_REDUCER_HPP
#define CANONICAL_REDUCER_HPP

#include "stdafx.h"
#include "DataSet.hpp"

namespace canonical{

class CanonicalReducer
{
private:
	// Refactors rules by expanding them. I.e changes AB->CD
	// into the rules AB->C and AB-D
	void refactorRules(std::set<Rule*>* rules);
	// Removes rules that match the reflexitivity rule. I.e. changes
	// ABC->C, ABC->D, into ABC->D
	void removeReflexivity(std::set<Rule*>* rules);
	// Reduces the rules by finding rules that are redundant. This is the actual
	// core of the Canonical Reduction algorithm
	void reduceRules(std::set<Rule*>* rules);

	// This creates the 'result' set which is used when trying to find if the
	// rule can be elimated. It takes a set of instances representing 'result' and
	// a set of instances which represent an antecedent. It then assigns the antecedent's
	// into the result set.
	void getResult(std::set<Instance*>& result, std::set<Instance*>* instances);
	
	// Checks if the rule's consequent can be added to result. I.e. if result = ABC
	// & rule = A->C then result will get C added to it and it will return true
	bool addToResult(std::set<Instance*>& result, Rule* rule);

	// Checks to see if based on the result, that the rule can be removed from
	// the original set of rules
	bool removeRule(std::set<Instance*>& result, Rule* rule);
public:
	// Public accessor which begins the chain of methods that
	// will reduce a data set.
	void reduce(DataSet* dataSet);
};

}

#endif