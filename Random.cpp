#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <iostream>
using namespace std;
#include "random.h"



void Random::setSeed()
{
	idum = -579; //-long(time(NULL));
	srand( /*(unsigned)time( NULL )*/ 579 );
}

double Random::randomNumber()
{
	if(ran1(&idum)<0.5) return -ran1(&idum);
	else return ran1(&idum);
}

double Random::ran1(long *idum)
{
	// Random number generator of Park and Miller
	// with Bays-Durham shuffle and added safeguards
	// from Numerical Recipes in C 2nd Edition returns a number between 0 and 1
	
	const long IA = 16807;
	const long IM = 2147483647;
	const double AM = (1.0/IM);
	const long IQ = 127773;
	const long IR = 2836;
	const int NTAB = 32;
	const double NDIV = (1+(IM-1)/NTAB);
	const double EPS = 1.2e-7;
	const double RNMX = (1.0-EPS);
	
	int j;
	long k;
	static long iy = 0;
	static long iv[NTAB];
	double temp;
	
	if(*idum <= 0 || !iy) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		for(j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ;
			*idum=IA*((*idum)-k*IQ)-IR*k;
			if(*idum<0) (*idum) += IM;
			if(j<NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if((*idum)<0) (*idum) += IM;
	j=int(iy/NDIV);
	iy=iv[j];
	iv[j]=*idum;
	if((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}