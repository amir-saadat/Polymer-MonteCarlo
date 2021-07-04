#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
#include "Random.h"
#include "Bead.h"
#include "Polymer.h"


Bead* Polymer::getBead(int i)
{
	return beads[i];
}

void Polymer::bead_of_polymerMove(int j)
{
	Bead* tempbead;
	tempbead = getBead(j);
	tempbead->move();
	
}


void Polymer::bead_of_polymerBack(int j)
{
	Bead* tempbead;
	tempbead = getBead(j);
	tempbead->goBack();
}


bool Polymer::Potential_in_chain(int i)
{
	int count=0;
	for(int k=0;k<beads.size();k++){
		if(k!=i){
			if(k==i-1 || k==i+1){
				if(distance(i,k)>=beads[k]->getDiameter() && distance(i,k)<=1.5*beads[k]->getDiameter()){
					count++;
				}
			}
			else{
				if(distance(i,k)>=beads[k]->getDiameter()){
					count++;
				}
			}
		}
	}
	if(count == (beads.size()-1)){
		return true;
	}
	else{
		return false;
	}
}


double Polymer::distance(int i,int j){
	Bead* bead1;
	Bead* bead2;
	double dx,dy,dz;
	bead1 = getBead(i);
	bead2 = getBead(j);
	dx = bead1->getX() - bead2->getX();
	dy = bead1->getY() - bead2->getY();
	dz = bead1->getZ() - bead2->getZ();
	return sqrt(pow(dx,2.0) + pow(dy,2.0) + pow(dz,2.0));

}
