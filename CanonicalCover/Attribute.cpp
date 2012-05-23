#include "Attribute.hpp"

using namespace std;

namespace canonical{

Attribute::Attribute(char* name, std::set<char*>* values)
{
	m_values = values;
	m_name = name;
}

bool Attribute::isValid(Instance* instance)
{
	set<char*>::iterator it = m_values->begin();
	
	// Check if instace is of this attribute type
	if( strcmp(instance->get_name(), m_name) )
		return false;

	// Check to see if there is a matching value
	while( it != m_values->end() )
	{
		// It's valid, replace the instance parameter
		// to use pointers to memory already allocated
		// by this attribute
		if( !strcmp(instance->get_value(),(*it)) )
		{
			// Replace the instances value and name
			// with the memory already allocated
			// for this attribute
			instance->set_name(m_name);
			instance->set_value(*it);
			return true;
		}
		it++;
	}
	// Does not free memory if Instance is not valid.
	return false;
}

char* Attribute::get_name()
{
	return m_name;
}

set<char*>* Attribute::get_values()
{
	return m_values;
}

bool Attribute::operator< (Attribute& other)
{
	// Check names first
	int result = strcmp( get_name(),other.get_name() );

	// this comes before other
	if( result < 0)
		return true;
	if( !result ) // they are equal
	{
		std::set<char*>::iterator thisIt = m_values->begin();
		std::set<char*>::iterator oIt = other.m_values->begin();
	
		while( thisIt != m_values->end() 
			&& oIt != other.m_values->end() )
		{
			result = strcmp( (*thisIt), (*oIt) );

			// this value comes after others value
			if(result > 0)
				return false;
			// this value comes before the others value
			if(result < 0)
				return true;
				
			thisIt++;
			oIt++;
		}
	
		// r1 comes first since it has less values
		if(thisIt != m_values->end() )
			return true;

	}

	return false;
}

Attribute::~Attribute()
{
	delete m_name;
	
	set<char*>::iterator it = m_values->begin();
	set<char*>::iterator temp = m_values->begin();

	while( it != m_values->end() )
	{
		temp++;
		delete (*it);
		m_values->erase(it);
		it = temp;
	}

	delete m_values;
}

}