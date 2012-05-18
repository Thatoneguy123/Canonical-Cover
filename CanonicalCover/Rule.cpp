#include "Rule.hpp"

using namespace std;

namespace canonical{

Rule::Rule()
{
	m_antecedent = new list<Instance*>();
	m_consequent = new list<Instance*>();
}

list<Instance*>* Rule::get_antecedents()
{
	return m_antecedent;
}

list<Instance*>* Rule::get_consequents()
{
	return m_consequent;
}

void Rule::add_antecedent(Instance* instance)
{
	m_antecedent->push_back(instance);
}

void Rule::add_consequent(Instance* instance)
{
	m_consequent->push_back(instance);
}
Rule::~Rule()
{
	list<Instance*>::iterator it = m_antecedent->begin();
	list<Instance*>::iterator temp = m_antecedent->begin();

	while( it != m_antecedent->end() )
	{
		temp++;
		delete (*it);
		m_antecedent->erase(it);
		it = temp;
	}

	delete m_antecedent;

	it = m_consequent->begin();
	temp = m_consequent->end();
	while( it != m_consequent->end() )
	{
		temp++;
		delete (*it);
		m_consequent->erase(it);
		it = temp;
	}

	delete m_consequent;
}

bool Rule::operator< (const Rule& other)
{
	return this->m_antecedent->size() < other.m_antecedent->size();
}

bool Rule::operator== (const Rule& other)
{
	std::list<Instance*>::iterator oIt = other.m_antecedent->begin();
	std::list<Instance*>::iterator mIt = this->m_antecedent->begin();

	// Check antecedents
	if( other.m_antecedent->size() != this->m_antecedent->size() )
		return false;
	else
	{
		while( mIt != m_antecedent->end() )
		{
			if( !((**mIt) == (**oIt)) )
				return false;
			else
			{
				mIt++; oIt++;
			}
		}
	}

	// Check consequents
	oIt = other.m_consequent->begin();
	mIt = this->m_consequent->begin();

	if( other.m_consequent->size() != this->m_consequent->size() )
		return false;
	else
	{
		while( mIt != m_consequent->end() )
		{
			if( (*mIt) != (*oIt) )
				return false;
			else
			{
				mIt++; oIt++;
			}
		}
	}

	// No cases failed
	return true;
}

}