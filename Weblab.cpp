#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>
using namespace std;
#include "Weblab.h"

void WebLab::openFile()
{
	stream = fopen( file_name.c_str(), "w" );
	assert(stream);
}

void WebLab::writeHeader(int i)
{
	fprintf( stream, "MODEL\t" "%d\n", i);
}

void WebLab::writePosition(int i,char chain,int chainint,double x,double y,double z)
{
	if(i<10)
		fprintf( stream, "ATOM     " "%d" "  H   MET " "%c" "   %d      " "%.3lf " "%.3lf " "%.3lf  " "1.00  " "0.00        C\n", i, chain, chainint, x, y, z );
	if(i>=10 && i<100)
		fprintf( stream, "ATOM    " "%d" "  H   MET " "%c" "   %d      " "%.3lf " "%.3lf " "%.3lf  " "1.00  " "0.00        C\n", i, chain, chainint, x, y, z );
	if(i>=100)
		fprintf( stream, "ATOM   " "%d" "  H   MET " "%c" "   %d      " "%.3lf " "%.3lf " "%.3lf  " "1.00  " "0.00        C\n", i, chain, chainint, x, y, z );
}

void WebLab::writeEnd()
{
	fprintf( stream, "ENDMDL\n" );
}