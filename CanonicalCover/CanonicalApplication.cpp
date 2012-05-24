#include "CanonicalApplication.hpp"

namespace canonical {

CanonicalApplication::CanonicalApplication()
{
	FILE *file = freopen("test4.txt","r",stdin);
	m_dataSetParser = new DataSetParser(m_io);
	m_canonicalReducer = new CanonicalReducer();
	m_io = new IO();
	m_io->clear();
}

void CanonicalApplication::run(int argc, char* argv[])
{
	this->parseCmdLineArgs(argc,argv);

	try
	{
		// Get the data set
		DataSet* dataSet = m_dataSetParser->parseFromInput();
		// Reduce the dataset
		m_canonicalReducer->reduce(dataSet);

		printSet(dataSet);
	}
	catch(std::runtime_error &e)
	{
		cerr << e.what() << endl;
		char a;
		cin >> a;
	}
}

void CanonicalApplication::parseCmdLineArgs(int argc,char* argv[])
{
	// Return if application name is only arg
	if(argc == 1) return;

	for(int i=1; i < argc; i++)
	{
		// Check for help flag
		if( !strcmp(argv[i],"-h") || !strcmp(argv[i],"--help"))
			this->usage();
	}
}

void CanonicalApplication::usage()
{
	cout << "Program will find the canonical cover of a given data set.\n"
			"Input must match the following format..\n\n"
			"<# Attributes>\n"
			"<attribute1> <value1> <value2> <valueN>\n" 
			"<attribute2> <value1> <value2> <valueN>\n"
			"<attributeN> <value1> <value2> <valueN>\n"
			"<# Rules>\n"
			"<attributeX>=<valueN> <attributeY>=<valueN> == "
			"<attributeZ>=<valueN> <attributeW>=<valueN>" << endl;
	
	m_io->pause();
	m_io->clear();

	cout << "Example.." << endl;
	cout << "2" << endl;
	cout << "color red blue" << endl;
	cout << "doors 4 2" << endl;
	cout << "1" << endl;
	cout << "color=red == doors=4" << endl;

	m_io->pause();
	m_io->clear();
}

void CanonicalApplication::printSet(DataSet* dataSet)
{
	set<Rule*>::iterator it = dataSet->get_rules()->begin();

	while( it != dataSet->get_rules()->end() )
	{
		set<Instance*>::iterator anteIt = (*it)->get_antecedents()->begin();
		set<Instance*>::iterator conseIt = (*it)->get_consequents()->begin();

		while( anteIt != (*it)->get_antecedents()->end() )
		{
			cout << (*anteIt)->get_name() << "=" << (*anteIt)->get_value() << " ";
			anteIt++;
		}

		cout << "== ";

		while( conseIt != (*it)->get_consequents()->end() )
		{
			cout << (*conseIt)->get_name() << "=" << (*conseIt)->get_value() << " ";
			conseIt++;
		}

		cout << endl;
		it++;
	}

	while(true)
	{
	}
}
CanonicalApplication::~CanonicalApplication()
{
	delete m_dataSetParser;
	delete m_io;
	delete m_canonicalReducer;
}

} // namespace