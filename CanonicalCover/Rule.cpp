#include "Rule.hpp"

using namespace std;

namespace canonical{

Rule::Rule()
{
	m_antecedent = new set<Instance*>();
	m_consequent = new set<Instance*>();
}

set<Instance*>* Rule::get_antecedents()
{
	return m_antecedent;
}

set<Instance*>* Rule::get_consequents()
{
	return m_consequent;
}

void Rule::add_antecedent(Instance* instance)
{
	m_antecedent->insert(instance);
}

void Rule::add_consequent(Instance* instance)
{
	m_consequent->insert(instance);
}
Rule::~Rule()
{
	set<Instance*>::iterator it = m_antecedent->begin();
	set<Instance*>::iterator temp = m_antecedent->begin();

	while( it != m_antecedent->end() )
	{
		temp++;
		delete (*it);
		m_antecedent->erase(it);
		it = temp;
	}

	delete m_antecedent;

	it = m_consequent->begin();
	temp = m_consequent->begin();
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
	// If this has less antecedents is  less than
	if( m_antecedent->size() < other.m_antecedent->size() )
		return true;
	
	// if other has more antecedents other is larger
	if( m_antecedent->size() > other.m_antecedent->size() )
		return false;

	// They are equal compare each element..
	set<Instance*>::iterator mIt = m_antecedent->begin();
	set<Instance*>::iterator oIt = other.m_antecedent->begin();

	while( mIt != m_antecedent->end()
		&& oIt != other.m_antecedent->end())
	{
		// If this antecedent is less than other
		// return true
		if( (**mIt) < (**oIt) )
			return true;
		else // if they are not equal it means the other
			// was larger
			if( !(**mIt == **oIt) )
				return false;
		mIt++; oIt++;
	}

	// If this has less consequents it is  less than
	if( m_consequent->size() < other.m_consequent->size() )
		return true;
	
	// if other has more consequents other is larger
	if( m_consequent->size() > other.m_consequent->size() )
		return false;

	//Check consequents
	mIt = m_consequent->begin();
	oIt = other.m_consequent->begin();

	while( mIt != m_consequent->end()
		&& oIt != other.m_consequent->end())
	{
		// If this antecedent is less than other
		// return true
		if( (**mIt) < (**oIt) )
			return true;
		else // if they are not equal it means the other
			// was larger
			if( !(**mIt == **oIt) )
				return false;
		mIt++; oIt++;
	}

	return false;
}

bool Rule::operator== (const Rule& other)
{
	std::set<Instance*>::iterator oIt = other.m_antecedent->begin();
	std::set<Instance*>::iterator mIt = this->m_antecedent->begin();

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