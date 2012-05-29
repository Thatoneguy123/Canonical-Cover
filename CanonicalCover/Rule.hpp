/**
 * Class defines a rule for the data set. That is
 * a set of instances which are antecedents and a
 * set of instances which are consequents
 */
#ifndef RULE_HPP
#define RULE_HPP

#include "Instance.hpp"

namespace canonical{

class Rule
{
private:
	// A set of instances which represent the
	// antecedents in the rule
	std::set<Instance*>* m_antecedent;
	// A set of instances which represent the
	// consequents in the rule
	std::set<Instance*>* m_consequent;
public:
	Rule();
	// Deletes all memory associated with this rule.
	// calls deleted on all instances in the antecedent
	// and consequent sets
	~Rule();
	// Adds an instance to the antecedents for this rule
	void add_antecedent(Instance* instance);
	// Adds an instance to the consequents for this rule
	void add_consequent(Instance* instance);

	// Returns a points to the set of antecedents
	std::set<Instance*>* get_antecedents();
	// Returns a pointer to the set of consequents
	std::set<Instance*>* get_consequents();

	// Checks if two rules are equal. Rules are equal
	// based on if all the antecednts and all the consequents
	// are equal
	bool operator== (const Rule& other);
	// Compares all the antecedents and consequents using their 
	// < operator. Sorts the rules either by which has the least
	// number of antecendets followed by consequents or if they are
	// inequal in those cases by whichever occurs first in alphabet
	// following instances < operator.
	bool operator< (const Rule& other);
};

}

// Less comparsion for sorting in a set. Sorts by least antecedents to most
namespace std{
	template<>
	struct less<canonical::Rule*>
	{
		bool operator()(canonical::Rule* r1,canonical::Rule* r2)
		{
			return (*r1) < (*r2);
		}
	};
}

#endif