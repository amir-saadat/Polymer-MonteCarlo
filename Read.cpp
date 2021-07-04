#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;
#include "Read.h"


void Read::openFile()
{
	stream = fopen( filename.c_str(), "r" );
	assert(stream);
}

vector<double> Read::getLine()
{
	vector<double> doubles;
	double x,y,z;
	fscanf( stream, "%lf\t" "%lf\t" "%lf\n", &x, &y, &z );
	doubles.push_back(x);
	doubles.push_back(y);
	doubles.push_back(z);
	return doubles;
}

double Read::getDouble()
{
	double rv;
	fscanf( stream, "%lf\n", &rv );
	return rv;
}

int Read::getInt()
{
	int rv;
	fscanf( stream, "%d\n", &rv);
	return rv;
}

void Read::skipLine()
{
	char junk[15];
	fscanf( stream, "%s\n", junk );
}

void Read::closeFile()
{
	if(stream) fclose( stream );
}
