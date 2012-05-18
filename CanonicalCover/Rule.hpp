#ifndef RULE_HPP
#define RULE_HPP

#include "Instance.hpp"

namespace canonical{

class Rule
{
private:
	std::set<Instance*>* m_antecedent;
	std::set<Instance*>* m_consequent;
public:
	Rule();
	~Rule();
	void add_antecedent(Instance* instance);
	void add_consequent(Instance* instance);

	std::set<Instance*>* get_antecedents();
	std::set<Instance*>* get_consequents();
	
	bool operator== (const Rule& other);
	bool operator< (const Rule& other);
};

}

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