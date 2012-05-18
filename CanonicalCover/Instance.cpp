#include "Instance.hpp"

namespace canonical{

Instance::Instance(char* name, char* value)
{
	m_name = name;
	m_value = value;
}

Instance::~Instance()
{
	delete m_name;
	delete m_value;
}

char* Instance::get_name()
{
	return m_name;
}

char* Instance::get_value()
{
	return m_value;
}

bool Instance::operator<(Instance& other)
{
	// Check names first
	int result = strcmp(get_name(),other.get_name() );
	
	// This comes before other in alphabet
	if( result < 0 )
		return true;
	else
		if( result == 0) // Equal so check values
		{
			result = strcmp(get_value(),other.get_value());
			// This value comes before other
			if( result < 0)
				return true;
		}

	// this comes After other so its greater than
	return false;
}

bool Instance::operator==(const Instance& other)
{
	return ( !strcmp(m_name,other.m_name) && !strcmp(m_value,other.m_value) );
}

}