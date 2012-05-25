Canonical-Cover
===============

A small console based c++ application which parses data sets and finds a canonical cover.

Building
--------
Project contains the entire VS 2012 source files and solution. Source files are of course available for you to create your own makefiles or do as you wish.


Supported Format
----------------

The program parses data that is CSC 464 Data Mining format. The format is as follows...

	#attributes
	<attribute name1> <attribute value1> <attribute valueN>
	<attribute nameN> <attribute value1> <attribute valueN>
	#rules/relations
	<attribute name>=<attribute value> == <attribute name>=<attribute value>

And an example with 'real' data...

	2
	color red blue
	doors 4 2
	1
	color=red == doors=4

Usage
------------

	CanonicalCover.exe -h
	CanonicalCover.exe -help
	CanonicalCover.exe -F "test.txt"
	CanonicalCover.exe -f "test.txt"

Contributing
------------

1. Fork it.
2. Create a branch
3. Commit your changes
4. Push to the branch
5. Create an Issue with a link to your branch
6. Diet Coke is awful