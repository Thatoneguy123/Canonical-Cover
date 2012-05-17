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
	std::set<Attribute*>* m_attributeDef;
	std::set<Rule*,RuleComp>* m_rules;
public:
	DataSet();
	~DataSet();

	void addAttributeDefinition(Attribute* attrib); // Adds attribute to definitions
	void addRuleDefinition(Rule* rule); // Adds rule to rule set
	bool isValid(Instance* instance); // Checks if instance is a valid attribute by definitions
	std::set<Attribute*>* get_attributes(); // returns all attrib defs
	std::set<Rule*,RuleComp>* get_rules(); // returns all rule set
};

}

#endif