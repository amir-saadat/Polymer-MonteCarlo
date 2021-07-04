#include <vector>
#include <assert.h>
#include <iostream>
#include <math.h>
using namespace std;
#include "Random.h"
#include "Bead.h"
#include "Polymer.h"
#include "Box.h"


double Box::distance(int i,int j,int k,int q)
{
	Bead* temp1;
	Bead* temp2;
	temp1 = polymers[i]->getBead(j);
	temp2 = polymers[k]->getBead(q);
	double dx = fabs( temp1->getX() - temp2->getX());
	double dy = fabs( temp1->getY() - temp2->getY() );
	double dz = fabs( temp1->getZ() - temp2->getZ() );
	if(dx > 0.50 * x) dx = fabs( dx - x );
	if(dy > 0.50 * y) dy = fabs( dy - y );
	if(dz > 0.50 * z) dz = fabs( dz - z );
	return sqrt(pow(dx,2.0) + pow(dy,2.0) + pow(dz,2.0));
}

double Box::angle(int ip,int i,int j,int k)
{
	Bead* temp1;
	Bead* temp2;
	Bead* temp3;
	temp1 = polymers[ip]->getBead(i);//
	temp2 = polymers[ip]->getBead(j);//last bead
	temp3 = polymers[ip]->getBead(k);//next bead
	double vx1 = ( temp2->getX() - temp1->getX());
	double vy1 = ( temp2->getY() - temp1->getY() );
	double vz1 = ( temp2->getZ() - temp1->getZ() );
	double vx2 = ( temp3->getX() - temp1->getX());
	double vy2 = ( temp3->getY() - temp1->getY() );
	double vz2 = ( temp3->getZ() - temp1->getZ() );
	double dx1 = fabs( temp2->getX() - temp1->getX());
	double dy1 = fabs( temp2->getY() - temp1->getY() );
	double dz1 = fabs( temp2->getZ() - temp1->getZ() );
	double v1 = sqrt(pow(dx1,2.0) + pow(dy1,2.0) + pow(dz1,2.0));
	double dx2 = fabs( temp3->getX() - temp1->getX());
	double dy2 = fabs( temp3->getY() - temp1->getY() );
	double dz2 = fabs( temp3->getZ() - temp1->getZ() );
	double v2 = sqrt(pow(dx2,2.0) + pow(dy2,2.0) + pow(dz2,2.0));
	return acos((vx1*vx2+vy1*vy2+vz1*vz2)/(v1*v2));
	
}

//int CheckPolymer;//Number of polymer 

int Box::move(int polymerSize)
{
	for(int i=0;i<polymers.size();i++){
		for(int j=0;j<polymerSize;j++){
			polymers[i]->bead_of_polymerMove(j);
			
			if(polymers[i]->Potential_in_chain(j) && Potential_between_chains(i,j,polymerSize) && CheckAngle(i,j,polymerSize)){
				//cout << "bead move accepted" << endl;
			}
			else{
				polymers[i]->bead_of_polymerBack(j);
			}
		}		
	}
	
	////moving Box
	x_old = x;
	y_old = y;
	z_old = z;
	x = x_old + random.randomNumber()*max_box_step_size;
	y = y_old + random.randomNumber()*max_box_step_size;
	z = z_old + random.randomNumber()*max_box_step_size;
	Bead* temp_bead;
	for(int i=0;i<polymers.size();i++){
		for(int j=0;j<polymerSize;j++) {
			temp_bead = polymers[i]->getBead(j);
			temp_bead->setX(temp_bead->getX()*x/x_old);
			temp_bead->setY(temp_bead->getY()*y/y_old);
			temp_bead->setZ(temp_bead->getZ()*z/z_old);
		}
	}
	
	for(int i=0;i<polymers.size();i++){
		for(int j=0;j<polymerSize;j++){
			if(polymers[i]->Potential_in_chain(j) && Potential_between_chains(i,j,polymerSize) && CheckAngle(i,j,polymerSize)){
				
			}
			else{
				for(int i=0;i<polymers.size();i++){
					for(int j=0;j<polymerSize;j++) {
						temp_bead = polymers[i]->getBead(j);
						temp_bead->setX(temp_bead->getX()*x_old/x);
						temp_bead->setY(temp_bead->getY()*y_old/y);
						temp_bead->setZ(temp_bead->getZ()*z_old/z);
					}
				}
				x = x_old;
				y = y_old;
				z = z_old;
				//cout<<"Box Move Did Not Accept"<<endl;
				return 0;
			}
		}
	}		
	
	//cout << "box move accepted" << endl;
	return 0;

}


bool Box::Potential_between_chains(int i,int j,int polymerSize)
{
	int accept=0;
	Bead* temp1;
	Bead* temp2;
	temp1 = polymers[i]->getBead(j);
	for(int k=0;k<polymers.size();k++){
		for(int q=0;q<polymerSize;q++){
			if(i==k && j==q){
			
			}
			else{
				temp2 = polymers[k]->getBead(q);
				if(distance(i,j,k,q) >= temp1->getDiameter()){
					
					accept++;
				}
			}
		}	
	}
	
	if(accept == (polymers.size()*polymerSize-1)){
		return true;
	}
	else{
		return false;
	}
}

bool Box::CheckAngle(int i,int j,int polymerSize){
	//for the first bead in chain
	if(j==0){
		if (angle(i,j+1,j,j+2) >=2){
			return true;
		}
		else {
			return false;
		}
		
	}
	// for the last bead in chain
	if(j==polymerSize-1){
		if (angle(i,j-1,j-2,j) >=2){
			return true;
		}
		else {
			return false;
		}
		
	}
	//for the second bead in chain
	if(j==1){
		if (angle(i,j,j-1,j+1)>=2 && angle(i,j+1,j,j+2)>=2){
			return true;
		}
		else {
			return false;
		}
		
	}
	// for the one bead before last bead in chain
	if(j==polymerSize-2){
		if (angle(i,j,j-1,j+1) >=2 && angle(i,j-1,j-2,j) >=2){
			return true;
		}
		else {
			return false;
		}
		
	}
	// for the rest of the beads in chain
	if(j!=0 && j!=1 && j!=polymerSize-2 && j!=polymerSize-1){
		if (angle(i,j,j-1,j+1) >=2 && angle(i,j-1,j-2,j) >=2 && angle(i,j+1,j,j+2) >=2){
			return true;
		}
		else {
			return false;
		}
		
	}
}

	