#ifndef RULE_HPP
#define RULE_HPP

#include "Instance.hpp"

namespace canonical{

class Rule
{
private:
	std::list<Instance*>* m_antecedent;
	std::list<Instance*>* m_consequent;
public:
	Rule();
	~Rule();
	void add_antecedent(Instance* instance);
	void add_consequent(Instance* instance);
};

}

#endif