#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Random.h"
#include "Bead.h"


void Bead::move()
{
	x_old = x;
	y_old = y;
	z_old = z;
	x = x + random.randomNumber()*max_step_size;
	y = y + random.randomNumber()*max_step_size;
	z = z + random.randomNumber()*max_step_size;
}

void Bead::goBack()
{
	x = x_old;
	y = y_old;
	z = z_old;
}
