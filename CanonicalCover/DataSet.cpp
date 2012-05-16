#include "DataSet.hpp"

using namespace std;

namespace canonical {

DataSet::DataSet()
{
	m_attributeDef = new set<Attribute*>();
	m_rules = new set<Rule*>();
}

void DataSet::addAttributeDefinition(Attribute *attrib)
{
	m_attributeDef->insert(attrib);
}

void DataSet::addRuleDefinition(Rule* rule)
{
	m_rules->insert(rule);
}
//TODO: Check if instance is valid
bool DataSet::isValid(Instance* instance)
{
	set<Attribute*>::iterator it = m_attributeDef->begin();
	
	while(it != m_attributeDef->end())
	{
		// Check if instance is valid
		if( (*it)->isValid(instance) )
			return true;

		it++;
	}

	return false;
}

std::set<Attribute*>* DataSet::get_attributes()
{
	return m_attributeDef;
}

std::set<Rule*>* DataSet::get_rules()
{
	return m_rules;
}

DataSet::~DataSet()
{
	set<Attribute*>::iterator it = m_attributeDef->begin();
	set<Attribute*>::iterator temp = m_attributeDef->begin();

	while( it != m_attributeDef->end())
	{
		temp++;
		delete (*it);
		m_attributeDef->erase(it);
		it = temp;
	}
	delete m_attributeDef;

	set<Rule*>::iterator itt = m_rules->begin();
	set<Rule*>::iterator ttemp = m_rules->begin();

	while( itt != m_rules->end())
	{
		ttemp++;
		delete (*itt);
		m_rules->erase(itt);
		itt = ttemp;
	}

	delete m_rules;
}

}