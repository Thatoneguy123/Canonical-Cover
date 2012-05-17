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

	std::list<Instance*>* get_antecedents();
	std::list<Instance*>* get_consequents();

	friend class RuleComp;
};

// This is the comparator to sort the rules in the set
class RuleComp
{
public:
	bool operator()(Rule* r1, Rule* r2)
	{
		// If r1 > r2 return true. This keeps largest sets at beginning.
		return r1->m_antecedent->size() > r2->m_antecedent->size();
	}
};

}

#endif