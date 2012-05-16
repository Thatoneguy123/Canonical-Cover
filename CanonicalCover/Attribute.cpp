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

	while( it != m_values->end() )
	{
		if( !strcmp(instance->get_value(),(*it)) )
			return true;
		it++;
	}

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