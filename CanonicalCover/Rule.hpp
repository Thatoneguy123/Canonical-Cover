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
	
	bool operator< (const Rule& other);
	bool operator== (const Rule& other);
};

}

namespace std{
	template<>
	struct less<canonical::Rule*>
	{
		bool operator()(canonical::Rule* r1,canonical::Rule* r2)
		{
			size_t r1Size = r1->get_antecedents()->size();
			size_t r2Size = r2->get_antecedents()->size();

			if( r1Size > r2Size && !(*r1 == *r2))
				return true;
			if( r2Size > r1Size && !(*r1 == *r2))
				return false;
			if( !(*r1 == *r2) )
				return true;
			
			return false;

		}
	};
}

#endif