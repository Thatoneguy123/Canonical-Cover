/**
 * Class implements a data set which is made up of attribute
 * definitions and a set of rules based off of these attributes
 */
#ifndef DATA_SET_HPP
#define DATA_SET_HPP

#include "stdafx.h"
#include "Attribute.hpp"
#include "Instance.hpp"
#include "Rule.hpp"

namespace canonical
{

class DataSet
{
private:
	// Set of attribute's that provide the defitions of attributes
	// which constitue which Instances are 'legal' within this dataset
	std::set<Attribute*>* m_attributeDef;
	// The set of rules for this data set which are created based off
	// the attribute definitions
	std::set<Rule*>* m_rules;
public:
	DataSet();
	~DataSet();

	// Adds an attribute to the set of definitions
	void addAttributeDefinition(Attribute* attrib);
	// Adds a rule to the set of rule definitions
	void addRuleDefinition(Rule* rule);
	// Checks to see if a particular instance is valid within
	// the attribute definitions created for this data set
	bool isValid(Instance* instance);
	// Returns set of all attributes that exist in this data set
	std::set<Attribute*>* get_attributes();
	// Returns set of all rules that exist in this data set
	std::set<Rule*>* get_rules();
};

}

#endif