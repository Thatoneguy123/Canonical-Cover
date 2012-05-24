#include "CanonicalReducer.hpp"

using namespace std;

namespace canonical	{

void CanonicalReducer::reduce(DataSet* dataSet)
{
	set<Rule*>* rules = dataSet->get_rules();
	// Order is dependent
	refactorRules(rules);
	removeReflexivity(rules);
	reduceRules(rules);
	// End order dependent
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
			set<Instance*>::iterator conseqIt = (*it)->get_consequents()->begin();
			while(conseqIt != (*it)->get_consequents()->end() )
			{
				Rule *rule = new Rule();
				// Add antecedents to the new rule
				set<Instance*>::iterator anteIt = (*it)->get_antecedents()->begin();
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

// Removes rules that match the reflexivity rule
// I.e. if AB->B the rule will be deleted.
void CanonicalReducer::removeReflexivity(std::set<Rule*>* rules)
{
	set<Rule*>::iterator it = rules->begin();
	set<Rule*>::iterator temp = rules->begin();

	while( it != rules->end() )
	{
		// Reset temp to the current element
		temp = it;

		// Get the current rules consequent. Only one consequent at this point
		// since refactoring occurs first.
		set<Instance*>::iterator conseqIt = (*it)->get_consequents()->begin();
		// Iterate through all antecedents. If any of them match the consequent,
		// delete the rule
		set<Instance*>::iterator anteIt = (*it)->get_antecedents()->begin();
		bool removeRule = false;
		while(anteIt != (*it)->get_antecedents()->end() && !removeRule)
		{
			// If they are equal set flag to delete the rule
			if( (**anteIt) == (**conseqIt) )
				removeRule = true;
			anteIt++;
		}

		// Delete the rule
		if(removeRule)
		{
			temp++;
			rules->erase(it);
			// Revalidate it
			it=temp;
		}
		else
			it++;
	}
}

void CanonicalReducer::reduceRules(std::set<Rule*>* rules)
{
	// Get the iterator to progress through rules as well as temp to remove rules.
	// Use reverse since set organizes the rules in order of least antecedents to most
	set<Rule*>::reverse_iterator temp = rules->rbegin();
	set<Rule*>::reverse_iterator currentRule = rules->rbegin();
	// Check all the rules atleast once
	while( currentRule != rules->rend() )
	{
		set<Instance*> result;
		result.clear();
		// Get the current rule
		temp = currentRule;
		
		// Assign 'a' to result
		getResult(result,(*currentRule)->get_antecedents());

		
		// Iterate throgh all the rules checking to see if they can
		// be appended to result
		set<Rule*>::reverse_iterator inIt = rules->rbegin();
		while( inIt != rules->rend() )
		{
			// If inIt isn't the current rule, check to see if it can be added
			// to result
			if( inIt != currentRule && addToResult( result,(*inIt) ) )
			{
				// reset the iterator to the beginning and start checking
				// all the rules again
				inIt = rules->rbegin();
			}
			else
				inIt++;
		}

		// Check if rule can be removed
		if( removeRule(result, *currentRule) )
		{
			temp++;
			// Erase the element. Reverse iterator is off by -1
			// as compared to the position of the base iterator
			set<Rule*>::iterator tempIter = rules->erase( (++currentRule).base() );			
			currentRule = std::set<Rule*>::reverse_iterator(tempIter);
		}
		else // Rule stays
			currentRule++;
	}
}

bool CanonicalReducer::removeRule(std::set<Instance*>& result, Rule* rule)
{
	// Get the consequent
	Instance* consequent = *rule->get_consequents()->begin();
	
	if( result.find(consequent) != result.end())
		return true;
	else
		return false;
}

bool CanonicalReducer::addToResult(std::set<Instance*>& result, Rule* rule)
{
	// Get first element in result
	set<Instance*>::iterator it = result.begin();
	bool matched = false;

	// Get the number of antecedents that much be matched
	int numToMatch = rule->get_antecedents()->size();
	// Check all elements in result and see if there is a matching value in the
	// rules antecedents
	while( it != result.end() && !matched)
	{
		// Get first element in the antecedents
		set<Instance*>::iterator rIt = rule->get_antecedents()->begin();

		while( rIt != rule->get_antecedents()->end()  && !matched)
		{
			// Check if they are equal
			if( (**it) == (**rIt) )
			{
				matched = true;
				numToMatch--;
			}
			else
				rIt++;
		}

		// Move to next element in result and check it
		it++;
	}

	// Check if there was a match
	if( matched && numToMatch == 0 )
	{
		pair<set<Instance*>::iterator,bool> ret;
		// Add the consequent to result
		ret = result.insert( *(rule->get_consequents()->begin()) );

		return ret.second;
	}
	
	return false;
	
}

// Assigns all instances to the result set. Used when finding the reduced form
void CanonicalReducer::getResult(set<Instance*> &result, set<Instance*>* instances)
{
	set<Instance*>::iterator it = instances->begin();

	// Add all the elements from instance into result
	while( it != instances->end() )
	{
		result.insert( (*it) );
		it++;
	}
}

}