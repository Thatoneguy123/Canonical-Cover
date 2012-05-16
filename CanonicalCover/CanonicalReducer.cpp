#include "CanonicalReducer.hpp"

using namespace std;

namespace canonical	{

void CanonicalReducer::reduce(DataSet* dataSet)
{
	set<Rule*>* rules = dataSet->get_rules();
	refactorRules(rules);
	int i;
	cin >> i;
}

// refactors rules such as A->BC, and EF->GH into
// A->B, A->C, EF->G, EF->H
void CanonicalReducer::refactorRules(set<Rule*>* rules)
{
	set<Rule*>::iterator it = rules->begin();
	set<Rule*>::iterator temp = rules->begin();

	while( it != rules->end() )
	{
		// Reset temp to the current element
		temp = it;

		// Check if the rule has more than one consequent
		if( (*it)->get_consequents()->size() > 1)
		{
			// Break the rule into multiple rules
			list<Instance*>::iterator conseqIt = (*it)->get_consequents()->begin();
			while(conseqIt != (*it)->get_consequents()->end() )
			{
				Rule *rule = new Rule();
				// Add antecedents to the new rule
				list<Instance*>::iterator anteIt = (*it)->get_antecedents()->begin();
				while( anteIt != (*it)->get_antecedents()->end() )
				{
					rule->add_antecedent( (*anteIt) );
					anteIt++;
				}

				// Add the consequent to the new rule
				rule->add_consequent( (*conseqIt) );
				// Add the new rule to the rules set
				rules->insert(rule);
				conseqIt++;
			}

			temp++;
			// Remove the old rule
			rules->erase(it);
			it = temp;
		}
		else
			it++;
	}
}

}