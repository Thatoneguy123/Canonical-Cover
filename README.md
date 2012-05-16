Canonical-Cover
===============

A small console based c++ application which parses data sets and finds a canonical cover.

Building
--------
Project contains the entire VS 2012 source files and solution. Source files are of course available for you to create your own makefiles or do as you wish.


Supported Format
----------------

The program parses data that is CSC 464 Data Mining format. The format is as follows...

	command(#attributes)
	command(<attribute name1> <attribute value1> <attribute valueN>)
	command(<attribute nameN> <attribute value1> <attribute valueN>)
	command(#rules/relations)
	command(<attribute name>=<attribute value> == <attribute name>=<attribute value>)

And an example with 'real' data...

	command(2)
	command(color red blue)
	command(doors 4 2)
	command(1)
	command(color=red == doors=4)

Contributing
------------

1. Fork it.
2. Create a branch
3. Commit your changes
4. Push to the branch
5. Create an [Issue][1] with a link to your branch
6. Diet Coke is awful