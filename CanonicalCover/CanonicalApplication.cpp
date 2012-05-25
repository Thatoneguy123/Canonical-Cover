#include "CanonicalApplication.hpp"

namespace canonical {

CanonicalApplication::CanonicalApplication()
{
	m_file = NULL;
	m_dataSetParser = new DataSetParser(m_io);
	m_canonicalReducer = new CanonicalReducer();
	m_io = new IO();
	m_io->clear();
}

void CanonicalApplication::run(int argc, char* argv[])
{
	bool running = true;
	DataSet* dataSet;

	this->parseCmdLineArgs(argc,argv);
	
	while( running)
	{
		m_io->clear();
		// If there was no file loaded with cmd line args 
		// get a file name from the user
		if( m_file == NULL )
		{
			cout << "Enter file name containing dataset: ";
			char* fileName = m_io->readString();
			getFile(fileName);
			delete fileName;
		}

		try
		{
			// Get the data set
			dataSet = m_dataSetParser->parseFromInput();
			// end the parse session
			endParseSession();
			// Reduce the dataset
			m_canonicalReducer->reduce(dataSet);
			printSet(dataSet);
		}
		catch(std::runtime_error &e)
		{
			endParseSession();
			cerr << e.what() << endl;
			m_io->pause();
		}
		delete dataSet;
		// Possible mem leak?...
		// m_file has been closed at this point however it it had been opened..
		m_file = NULL;
		// clear screen. See if user wants to go again
		running = getRunAgain();	
	}
}

bool CanonicalApplication::getRunAgain()
{
	m_io->clear();
	bool again = false;
	char* input = NULL;
	bool badInput = true;
	do
	{
		cout << "Would you like to run again for another dataset? (y)es or (n)o: ";
		input = m_io->readString();
		if( input == NULL)
			input = m_io->readString();

		if( !strcmp(input,"y") || !strcmp(input,"Y") )
		{
			again = true;
			badInput = false;
		}
		if( !strcmp(input,"n") || !strcmp(input,"N") )
		{
			again = false;
			badInput = false;
		}

		delete input;

	}while( badInput );

	// Read left over new line
	m_io->readString();
	return( again );
}
void CanonicalApplication::endParseSession()
{
	// Close the file if it was being used
	if( m_file != NULL)
	{
		_close( _fileno(m_file) );
		// Reset the stdin to use console
		_dup2(m_consoleFd, _fileno(stdin));
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
		// Check if a file is being passed in
		if( !strcmp(argv[i],"-f") || !strcmp(argv[i],"--F"))
			this->getFile(argv[++i]);
	}
}

void CanonicalApplication::getFile(char* fileArg)
{
#ifdef _WIN32
	// save the console FD
	m_consoleFd = _dup( _fileno(stdin) );
	// Set input to come from file
	m_file = freopen(fileArg,"r",stdin);
#endif
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
	// Get name of the file to write to
	cout << "Enter file name to save output: ";
	char* outFile = m_io->readString();
	// read left over newline
	m_io->readString();

	// Open file to write
	ofstream outputFile;
	outputFile.open(outFile);

	set<Rule*>::iterator it = dataSet->get_rules()->begin();

	// Iterate though all the rules printing them
	while( it != dataSet->get_rules()->end() )
	{
		set<Instance*>::iterator anteIt = (*it)->get_antecedents()->begin();
		set<Instance*>::iterator conseIt = (*it)->get_consequents()->begin();

		// Keeps track if first element printed. Helps with formatting..
		bool first = true;
		// print all antecedents for this rule
		while( anteIt != (*it)->get_antecedents()->end() )
		{
			if( !first )
			{
				cout << " ";
				outputFile << " " ;
			}
			first = false;
			cout << (*anteIt)->get_name() << "=" << (*anteIt)->get_value();
			outputFile << (*anteIt)->get_name() << "=" << (*anteIt)->get_value();
			anteIt++;
		}

		// Print the serpator that seperates antecedents and consequents
		cout << " == ";
		outputFile << " == ";

		first=true;
		// Print all consequents
		while( conseIt != (*it)->get_consequents()->end() )
		{
			if( !first )
			{
				cout << " ";
				outputFile << " " ;
			}
			first = false;

			cout << (*conseIt)->get_name() << "=" << (*conseIt)->get_value();
			outputFile << (*conseIt)->get_name() << "=" << (*conseIt)->get_value();
			conseIt++;
		}
		
		cout << endl;
		outputFile << endl;
		it++;
	}
	outputFile.close();
	delete outFile;
	m_io->pause();
}
CanonicalApplication::~CanonicalApplication()
{
	delete m_dataSetParser;
	delete m_io;
	delete m_canonicalReducer;
}

} // namespace